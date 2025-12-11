/*
 * SystemStateHandler.cpp
 *
 *  Created on: Nov 24, 2025
 *      Author: samay099
 */

#include "SystemStateHandler.h"
#include "SystemState.h"
#include "stm32f4xx_hal.h"
#include <iostream>

SystemState CurrentState = STATE_IDLE;

SystemStateHandler::SystemStateHandler() {
	//leds ausmachen
	vSetGreenLED(false);
	vSetRedLED(false);
	vSetBlueLED(false);
}

SystemStateHandler::~SystemStateHandler() {}

//statische instanz um sicherzustellen dass nur mit dieser einen gearbeitet wird
SystemStateHandler& SystemStateHandler::getObject() {
	static SystemStateHandler sObject;
	return sObject;
}


void SystemStateHandler::vSetGreenLED(bool on){

	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0, on ? GPIO_PIN_SET : GPIO_PIN_RESET);

	//std::cout<<"Green LED is"<<(on ? "on (Idle)" : "off")<<"\n";
}

void SystemStateHandler::vSetRedLED(bool on){

	HAL_GPIO_WritePin (GPIOB,  GPIO_PIN_14, on ? GPIO_PIN_SET : GPIO_PIN_RESET);

	//std::cout<<"Red LED is"<<(on ? "on (Cleanup)" : "off")<<"\n";

}
void SystemStateHandler::vSetBlueLED(bool on){

	HAL_GPIO_WritePin (GPIOB,  GPIO_PIN_7, on ? GPIO_PIN_SET : GPIO_PIN_RESET);

	//std::cout<<"Blue LED is"<<(on ? "on (Result)" : "off")<<"\n";

}


void SystemStateHandler::vTransition(SystemState NewState){

	CurrentState = NewState;

	vSetGreenLED(false);
	vSetRedLED(false);
	vSetBlueLED(false);


	switch(CurrentState) {

		
		case STATE_IDLE :
		
			vSetGreenLED(true);
			//std::cout<<"System is now in"<<NewState<<std::endl;
			break;

		case STATE_RUNNING:

			vSetGreenLED(true); //erstmal anmachen, soll in main aber blinken
			break;

		case STATE_CLEANUP:

			vSetRedLED(true);
			//std::cout<<"System is now in"<<NewState<<std::endl;
			break;

		case STATE_RESULT:

			vSetBlueLED(true);
			//std::cout<<"System is now in"<<NewState<<std::endl;
			break;

		case STATE_ERROR:

			vSetRedLED(true);
			break;

		default:
			//std::cout<<"Unhandled State: " <<NewState<<std::endl;
			break;
		

	}

}
