/*
 * Event.h
 *
 *  Created on: Dec 14, 2025
 *      Author: martin
 */

#ifndef SRC_EVENT_H_
#define SRC_EVENT_H_

#include <string>
#include <queue>
#include <vector>

#include "SystemState.h"
#include "main.h"

class Event;
extern std::queue<Event*> event_queue;
extern SystemState CurrentState;

class Event {
public:
	Event() = default;

	virtual void vHandleEvent() = 0;

	virtual ~Event() = default;
};

class DisplayEvent : public Event {
    std::string message;
public:
    DisplayEvent(std::string msg) : message(msg) {}
    void vHandleEvent() override;
};

class SystemStartEvent : public Event {
public:
    void vHandleEvent() override;
};

class StartTimeoutEvent : public Event {
public:
    void vHandleEvent() override;
};

class SystemIdleEvent : public Event {
public:
    void vHandleEvent() override;
};

class BlueButtonEvent : public Event {
public:
	BlueButtonEvent() = default;
	virtual ~BlueButtonEvent() = default;

    void vHandleEvent() override;
};

class StartMeasureEvent : public Event {
public:
    void vHandleEvent() override;
};

class CalculationEvent : public Event {
public:
    void vHandleEvent() override;
};

class FinalCalculationEvent : public Event {
    uint32_t totalTimeMs;
public:
    FinalCalculationEvent(uint32_t time) : totalTimeMs(time) {}
    void vHandleEvent() override;
};

class ResultTimeoutEvent : public Event {
public:
    void vHandleEvent() override;
};

class SystemCancelEvent : public Event {
public:
    void vHandleEvent() override;
};

class CancelTimeoutEvent : public Event {
public:
    void vHandleEvent() override;
};

#endif /* SRC_EVENT_H_ */
