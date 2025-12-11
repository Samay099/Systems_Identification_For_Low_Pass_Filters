/*
 * CancelEvent.cpp
 *
 *  Created on: Dec 10, 2025
 *      Author: Chrissi
 */

#include "CancelEvent.h"
#include "SystemStateHandler.h"
#include "SystemState.h"

extern SystemState CurrentState;

CancelEvent::CancelEvent() {}

void CancelEvent::vHandleEvent() {
	if(CurrentState == STATE_RUNNING) { //aber nur bei running??
		SystemStateHandler& handler = SystemStateHandler::getObject();

		handler.vTransition(STATE_CLEANUP);
	}
}

