/*
 * BlueButtonEvent.h
 *
 *  Created on: Dec 3, 2025
 *      Author: samay099
 */

#ifndef SRC_BLUEBUTTONEVENT_H_
#define SRC_BLUEBUTTONEVENT_H_

#include"Event.h"

class BlueButtonEvent : public Event  {
public:
	BlueButtonEvent();
	virtual ~BlueButtonEvent();

	void vHandleEvent();
};

#endif /* SRC_BLUEBUTTONEVENT_H_ */
