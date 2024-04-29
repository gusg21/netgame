//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_EVENTQUEUE_H
#define NETGAME_EVENTQUEUE_H

#include <deque>

#include "input.h"

namespace net {
#define EVENT_NONE_EVENT 0

struct KeyEventData {
    KeyCode Key;
    bool Pressed;
};
#define EVENT_KEY_EVENT 1

#define EVENT_QUIT_EVENT 2

struct CharEventData {
    char Char;
};
#define EVENT_CHAR_EVENT 3

struct MouseMotionEventData {
    float DeltaX, DeltaY;
    float X, Y;
};
#define EVENT_MOUSE_MOTION_EVENT 4

struct MouseButtonEventData {
    MouseButton Button;
    bool Pressed;
};
#define EVENT_MOUSE_BUTTON_EVENT 5

#define EVENT_ACK_JOIN_EVENT 6

struct ListLobbyNamesEventData {
    char names[256];
};
#define EVENT_LIST_LOBBY_NAMES_EVENT 7

#define EVENT_START_GAME_EVENT 8

struct CardState {
    uint32_t Id;
    uint32_t Value;
    float X;
    float Y;
};

#define EVENT_MAX_NUM_CARD_STATES 20
struct CardStateEventData {
    CardState States[EVENT_MAX_NUM_CARD_STATES] = { 0 };
};
#define EVENT_CARD_STATE_EVENT 9

struct CustomEventData {
    void* Data;
};
#define EVENT_CUSTOM_EVENT INT32_MAX

union EventData {
    KeyEventData AsKeyEvent;
    CharEventData AsCharEvent;
    MouseMotionEventData AsMouseMotionEvent;
    MouseButtonEventData AsMouseButtonEvent;
    ListLobbyNamesEventData AsListLobbyNamesEvent;
    CardStateEventData AsCardStateEvent;

    CustomEventData AsCustomEvent;

    uint32_t _;
};

struct Event {
    uint32_t Type;

    EventData Data = { ._ = 0 };
};

class EventQueue {
public:
    bool IsEmpty() { return m_Queue.empty(); };
    void PostEvent(Event event);
    Event GetNextEvent();
    void HandleThisEvent();
    void ResetEventReadHead();
    void ClearEvents() { m_Queue.clear(); };

private:
    std::deque<Event> m_Queue;
    uint32_t m_ReadHeadIndex = 0;
};
}

#endif