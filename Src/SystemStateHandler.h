/*
 * SystemStateHandler.h
 *
 *  Created on: Nov 24, 2025
 *      Author: samay099
 */

#ifndef SRC_SYSTEMSTATEHANDLER_H_
#define SRC_SYSTEMSTATEHANDLER_H_

#include "SystemState.h"

class SystemStateHandler
{
	private:
		void vSetGreenLED(bool on);
		void vSetRedLED(bool on);
		void vSetBlueLED(bool on);

	public:
		SystemStateHandler();

		void vTransition(SystemState NewState);



		virtual ~SystemStateHandler();
};

#endif /* SRC_SYSTEMSTATEHANDLER_H_ */
