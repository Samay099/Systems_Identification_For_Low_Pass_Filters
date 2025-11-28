/*
 * Event.h
 *
 *  Created on: Nov 24, 2025
 *      Author: samay099
 */

#ifndef SRC_EVENT_H_
#define SRC_EVENT_H_

#include<queue>

class Event {
public:
	Event();

	virtual void vHandleEvent() = 0;

	virtual ~Event() = default;
};

std::queue<Event*> event_queue;


#endif /* SRC_EVENT_H_ */
