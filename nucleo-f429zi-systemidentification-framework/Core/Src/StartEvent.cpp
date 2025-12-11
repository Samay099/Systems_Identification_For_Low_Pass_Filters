/*
 * StartEvent.cpp
 *
 *  Created on: Dec 4, 2025
 *      Author: Chrissi
 */

#include "StartEvent.h"
#include "SystemStateHandler.h"
#include "SystemState.h"
#include "main.h"

extern SystemStateHandler stateHandler;
extern SystemState CurrentState;

StartEvent::StartEvent() {}

void StartEvent::vHandleEvent() {
    if (CurrentState != STATE_IDLE) {
        return; // nichts machen wenn nicht idle
    }

    //von idle zu running
    SystemStateHandler& handler = SystemStateHandler::getObject();
    handler.vTransition(STATE_RUNNING);

    // hier NICHT das blinken implementieren, muss in die main loop
    // da sonst die event queue blockiert wird
}
