/*
 * Event.cpp
 *
 *  Created on: Dec 14, 2025
 *      Author: martin
 */

#include <cstdio>
#include "Event.h"
#include "main.h"
#include "SystemStateHandler.h"
#include "lcd.h"

extern std::queue<Event*> event_queue;
extern SystemStateHandler* sysHandler;
extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c2;
extern LCD_HandleTypeDef lcd;
extern uint32_t startTime;
extern uint32_t stateTimestamp;

// Definition threshold value (0,95*4095=3890,25)
#define THRESHOLD_3T 3890

void DisplayEvent::vHandleEvent() {

	LCD_Clear(&lcd);
	LCD_SetCursor(&lcd, 0, 0);

	// Switch trough all possible states and set display output
	switch(CurrentState){

		case STATE_STARTING:
			LCD_Printf(&lcd, "Booting...");

			break;

		case STATE_IDLE :

			LCD_Printf(&lcd, "State: IDLE");
			LCD_SetCursor(&lcd, 1, 0);
			LCD_Printf(&lcd, "BLUE to START");

			break;

		case STATE_RUNNING:

			LCD_Printf(&lcd, "State: RUNNING");
			LCD_SetCursor(&lcd, 1, 0);
			LCD_Printf(&lcd, "BLUE to CANCEL");

			break;

		case STATE_CLEANUP:

			LCD_Printf(&lcd, "State: CANCELED");
			LCD_SetCursor(&lcd, 1, 0);
			LCD_Printf(&lcd, "CLEANUP ...");

			break;

		case STATE_RESULT:

			LCD_Printf(&lcd, "State: COMPLETED");
			LCD_SetCursor(&lcd, 1, 0);
			LCD_Printf(&lcd, "%s", message.c_str());

			break;

		case STATE_ERROR:

			LCD_Printf(&lcd, "State: ERROR");
			LCD_SetCursor(&lcd, 1, 0);
			LCD_Printf(&lcd, "Restart device");

			break;

		default:
			break;
	}
}

void SystemStartEvent::vHandleEvent() {
	// Startup Event

	sysHandler->vTransition(STATE_STARTING);
	DisplayEvent("").vHandleEvent();
    event_queue.push(new StartTimeoutEvent());
}

void StartTimeoutEvent::vHandleEvent() {
	// Start timeout without blocking

    if (HAL_GetTick() - stateTimestamp < 1100) {
        event_queue.push(new StartTimeoutEvent());
    } else {
        event_queue.push(new SystemIdleEvent());
    }
}

void SystemIdleEvent::vHandleEvent() {
	// Idle Event showing operational

    sysHandler->vTransition(STATE_IDLE);
    event_queue.push(new DisplayEvent("IDLE: Blau druecken"));
}

void BlueButtonEvent::vHandleEvent() {
	// React to pressing of blue button depending on current state

	if (CurrentState == STATE_CLEANUP) {
		return;
	}
	else if (CurrentState == STATE_IDLE) {
        event_queue.push(new StartMeasureEvent());
    }
    else if (CurrentState == STATE_RUNNING) {
        event_queue.push(new SystemCancelEvent());
    }
    else if (CurrentState == STATE_RESULT) {
    	event_queue.push(new SystemCancelEvent());
    }
}

void StartMeasureEvent::vHandleEvent() {
	// Starting the measurement when blue button is pressed and STATE_IDLE

	sysHandler->vTransition(STATE_RUNNING);
	event_queue.push(new DisplayEvent("Start measuring"));

	// Give power to testing circuit
    HAL_GPIO_WritePin(RC_INPUT_GPIO_Port, RC_INPUT_Pin, GPIO_PIN_SET);

    startTime = HAL_GetTick();

    event_queue.push(new CalculationEvent());
}

void CalculationEvent::vHandleEvent() {
	// Measure time to reach 3T

    if (CurrentState != STATE_RUNNING) {
    	return;
    }

    HAL_ADC_Start(&hadc1);

    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
    	uint32_t adcValue = HAL_ADC_GetValue(&hadc1);

    	if (adcValue >= THRESHOLD_3T) {
    		uint32_t duration = HAL_GetTick() - startTime;
    		event_queue.push(new FinalCalculationEvent(duration));
    		return;
		}
	}
    // Loop trough Calculation Event to prevent blocking
    event_queue.push(new CalculationEvent());
}

void FinalCalculationEvent::vHandleEvent() {
	// Calculate the time constant and send it to the display

	// Stop power to testing circuit
    HAL_GPIO_WritePin(RC_INPUT_GPIO_Port, RC_INPUT_Pin, GPIO_PIN_RESET);

    sysHandler->vTransition(STATE_RESULT);

    char buffer[32];
    snprintf(buffer, sizeof(buffer), "T=%.1f ms", totalTimeMs / 3.0f);
    event_queue.push(new DisplayEvent(buffer));
    event_queue.push(new ResultTimeoutEvent());
}

void ResultTimeoutEvent::vHandleEvent() {
	// Give user enough time to read result without blocking

    if (HAL_GetTick() - stateTimestamp >= 5000) {
        event_queue.push(new SystemIdleEvent());
    }
    else {
        event_queue.push(new ResultTimeoutEvent());
    }
}

void SystemCancelEvent::vHandleEvent() {
	// Handle cancellation trough blue button press

    sysHandler->vTransition(STATE_CLEANUP);
    event_queue.push(new DisplayEvent(""));

    // Stop power to testing circuit
    HAL_GPIO_WritePin(RC_INPUT_GPIO_Port, RC_INPUT_Pin, GPIO_PIN_RESET);

    event_queue.push(new CancelTimeoutEvent());
}

void CancelTimeoutEvent::vHandleEvent() {
	// Give user time to read cleanup done without blocking

    if (HAL_GetTick() - stateTimestamp > 1000) {
        event_queue.push(new SystemIdleEvent());
    }
    else {
        event_queue.push(new CancelTimeoutEvent());
    }
}

