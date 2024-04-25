//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_EVENTQUEUE_H
#define NETGAME_EVENTQUEUE_H

#include <deque>
#include <raylib.h>

namespace net {
#define EVENT_NONE_EVENT 0

struct KeyEvent {
    uint32_t Key;
    bool Pressed;
};
#define EVENT_KEY_EVENT 1

struct QuitEvent {
    uint32_t _;
};
#define EVENT_QUIT_EVENT 2

struct CharEvent {
    char Char;
};
#define EVENT_CHAR_EVENT 3

struct CustomEvent {
    void* Data;
};
#define EVENT_CUSTOM_EVENT INT32_MAX

union EventData {
    KeyEvent AsKeyEvent;
    QuitEvent AsQuitEvent;
    CharEvent AsCharEvent;

    CustomEvent AsCustomEvent;
};

struct Event {
    uint32_t Type;

    EventData Data;
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