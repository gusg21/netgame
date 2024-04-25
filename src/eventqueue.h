//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_EVENTQUEUE_H
#define NETGAME_EVENTQUEUE_H

#include <deque>
#include <raylib.h>

namespace net {
#define EVENT_NONE 0

struct KeyEvent {
    uint32_t Key;
    bool Pressed;
};
#define EVENT_KEY_EVENT 1

struct QuitEvent {
	uint32_t _;
};
#define EVENT_QUIT_EVENT 2

struct CustomEvent {
    void* Data;
};
#define EVENT_CUSTOM_EVENT INT32_MAX

union Event {
    uint32_t Type;

    KeyEvent AsKeyEvent;
	QuitEvent AsQuitEvent;
    CustomEvent AsCustomEvent;
};

class EventQueue {
public:
    bool IsEmpty() { return m_Queue.empty(); };
    void PostEvent(Event event);
	Event GetNextEvent();
	void HandleThisEvent();
	void ResetEventReadHead();

private:
    std::deque<Event> m_Queue;
	uint32_t m_ReadHeadIndex = 0;
};
}

#endif