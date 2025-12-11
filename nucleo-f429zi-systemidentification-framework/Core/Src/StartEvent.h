/*
 * StartEvent.h
 *
 *  Created on: Dec 4, 2025
 *      Author: Chrissi
 */

#ifndef SRC_STARTEVENT_H_
#define SRC_STARTEVENT_H_
#include "Event.h"

class StartEvent : public Event {
public:
	StartEvent();
	virtual ~StartEvent() = default;

	void vHandleEvent() override;
};

#endif /* SRC_STARTEVENT_H_ */
