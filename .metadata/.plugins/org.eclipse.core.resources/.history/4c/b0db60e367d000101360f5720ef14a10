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

SystemState CurrentState = STATE_STARTING;

SystemStateHandler::SystemStateHandler() {
	// TODO Auto-generated constructor stub

}

SystemStateHandler::~SystemStateHandler() {
	// TODO Auto-generated destructor stub
}

void SystemStateHandler::vSetGreenLED(bool on){

	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);

	//std::cout<<"Green LED is"<<(on ? "on (Idle)" : "off")<<"\n";
}

void SystemStateHandler::vSetRedLED(bool on){

	HAL_GPIO_WritePin (GPIOB,  GPIO_PIN_14, GPIO_PIN_SET);

	//std::cout<<"Red LED is"<<(on ? "on (Cleanup)" : "off")<<"\n";

}
void SystemStateHandler::vSetBlueLED(bool on){

	HAL_GPIO_WritePin (GPIOB,  GPIO_PIN_7, GPIO_PIN_SET);

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

		case STATE_CLEANUP:

			vSetRedLED(true);
			//std::cout<<"System is now in"<<NewState<<std::endl;
			break;

		case STATE_RESULT:

			vSetBlueLED(true);
			//std::cout<<"System is now in"<<NewState<<std::endl;
			break;
		default:
			//std::cout<<"Unhandled State: " <<NewState<<std::endl;
			break;
		

	}

}
