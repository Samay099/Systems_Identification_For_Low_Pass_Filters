/*
 * CancelEvent.h
 *
 *  Created on: Dec 10, 2025
 *      Author: Chrissi
 */

#ifndef SRC_CANCELEVENT_H_
#define SRC_CANCELEVENT_H_

#include "Event.h"

class CancelEvent : public Event {
public:
	CancelEvent();
	virtual ~CancelEvent() = default;
	void vHandleEvent() override;
};

#endif /* SRC_CANCELEVENT_H_ */
