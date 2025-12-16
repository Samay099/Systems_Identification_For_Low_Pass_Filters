/*
 * SystemStateHandler.cpp
 *
 *  Created on: Nov 24, 2025
 *      Author: samay099
 */

#include "SystemStateHandler.h"
#include "SystemState.h"
#include "main.h"
#include <iostream>

extern SystemState CurrentState;
extern uint32_t stateTimestamp;

SystemStateHandler::SystemStateHandler() {
	// TODO Auto-generated constructor stub
}

SystemStateHandler::~SystemStateHandler() {
	// TODO Auto-generated destructor stub
}

void SystemStateHandler::vSetGreenLED(bool on) {

	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0, on ? GPIO_PIN_SET : GPIO_PIN_RESET);

	//std::cout<<"Green LED is"<<(on ? "on (Idle)" : "off")<<"\n";
}

void SystemStateHandler::vSetRedLED(bool on) {

	HAL_GPIO_WritePin (GPIOB,  GPIO_PIN_14, on ? GPIO_PIN_SET : GPIO_PIN_RESET);

	//std::cout<<"Red LED is"<<(on ? "on (Cleanup)" : "off")<<"\n";

}
void SystemStateHandler::vSetBlueLED(bool on) {

	HAL_GPIO_WritePin (GPIOB,  GPIO_PIN_7, on ? GPIO_PIN_SET : GPIO_PIN_RESET);

	//std::cout<<"Blue LED is"<<(on ? "on (Result)" : "off")<<"\n";

}

void SystemStateHandler::vBlinking() {
	// Set blinking of LEDs without blocking

    static uint32_t lastTime = 0;
    static uint8_t step = 0;
    static bool ledOn = false;

    uint32_t now = HAL_GetTick();

    switch (CurrentState)
    {
        case STATE_STARTING:
            if (now - lastTime >= 300)
            {
                vSetGreenLED(false);
                vSetBlueLED(false);
                vSetRedLED(false);

                if (step == 0) vSetGreenLED(true);
                if (step == 1) vSetBlueLED(true);
                if (step == 2) vSetRedLED(true);

                step = (step + 1) % 3;
                lastTime = now;
            }
            break;

        case STATE_RUNNING:
            if (now - lastTime >= 500)
            {
                ledOn = !ledOn;
                vSetGreenLED(ledOn);
                lastTime = now;
            }
            break;

        case STATE_ERROR:
            if (now - lastTime >= 200)
            {
                ledOn = !ledOn;
                vSetRedLED(ledOn);
                lastTime = now;
            }
            break;

        default:
            break;
    }
}

void SystemStateHandler::vTransition(SystemState NewState) {

	if (CurrentState == NewState) {
	        return;
	}

	CurrentState = NewState;

	stateTimestamp = HAL_GetTick();

	vSetGreenLED(false);
	vSetRedLED(false);
	vSetBlueLED(false);

	switch(CurrentState) {
		
		case STATE_STARTING:
			break;

		case STATE_IDLE:
			vSetGreenLED(true);
			break;

		case STATE_RUNNING:
			break;

		case STATE_CLEANUP:
			vSetRedLED(true);
			break;

		case STATE_RESULT:
			vSetBlueLED(true);
			break;

		case STATE_ERROR:
			break;

		default:
			break;
		
	}

}
