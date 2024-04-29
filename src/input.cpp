#include "input.h"

#include <raylib.h>
#include <raymath.h>

#include "eventqueue.h"

void net::Input::PostEvents(net::EventQueue* queue)
{
    int32_t charCode = ::GetCharPressed();
    while (charCode > 0) {
        bool readable = (charCode >= 32) && (charCode <= 125);
        if (readable || charCode == 0x08) { // 0x08 = backspace
            queue->PostEvent(Event {
                .Type = EVENT_CHAR_EVENT,
                .Data = { .AsCharEvent = CharEventData { .Char = (char)charCode } } });
        }

        charCode = ::GetCharPressed();
    }

    int32_t keyCode = 0;
    for (int32_t keyCode = 0; keyCode < INPUT_KEY_COUNT; keyCode++) {
        bool nowPressed = IsKeyDown((net::KeyCode)keyCode);
        bool wasPressed = m_PrevKeys[keyCode];

        if (nowPressed != wasPressed) {
            queue->PostEvent(Event {
                .Type = EVENT_KEY_EVENT,
                .Data = { .AsKeyEvent = KeyEventData { .Key = (net::KeyCode)keyCode, .Pressed = nowPressed } } });
        }
        
        m_PrevKeys[keyCode] = nowPressed;
    }

    Vector2 mouseDelta = ::GetMouseDelta();
    if (::Vector2Length(mouseDelta) > 0.f) {
        Vector2 mousePosition = ::GetMousePosition();
        queue->PostEvent(Event {
            .Type = EVENT_MOUSE_MOTION_EVENT,
            .Data = { .AsMouseMotionEvent = {
                          .DeltaX = mouseDelta.x, .DeltaY = mouseDelta.y, .X = mousePosition.x, .Y = mousePosition.y } } });
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        printf("Firing left click down event...\n");
        queue->PostEvent(Event {
            .Type = EVENT_MOUSE_BUTTON_EVENT,
            .Data = { .AsMouseButtonEvent = { .Button = MouseButton::LEFT, .Pressed = true } } });
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        printf("Firing left click up event...\n");
        queue->PostEvent(Event {
            .Type = EVENT_MOUSE_BUTTON_EVENT,
            .Data = { .AsMouseButtonEvent = { .Button = MouseButton::LEFT, .Pressed = false } } });
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        queue->PostEvent(Event {
            .Type = EVENT_MOUSE_BUTTON_EVENT,
            .Data = { .AsMouseButtonEvent = { .Button = MouseButton::RIGHT, .Pressed = true } } });
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
        queue->PostEvent(Event {
            .Type = EVENT_MOUSE_BUTTON_EVENT,
            .Data = { .AsMouseButtonEvent = { .Button = MouseButton::RIGHT, .Pressed = false } } });
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
        queue->PostEvent(Event {
            .Type = EVENT_MOUSE_BUTTON_EVENT,
            .Data = { .AsMouseButtonEvent = { .Button = MouseButton::MIDDLE, .Pressed = true } } });
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE)) {
        queue->PostEvent(Event {
            .Type = EVENT_MOUSE_BUTTON_EVENT,
            .Data = { .AsMouseButtonEvent = { .Button = MouseButton::MIDDLE, .Pressed = false } } });
    }
}

bool net::Input::IsKeyDown(KeyCode code)
{
    ::KeyboardKey rk = ::KEY_NULL;
    switch (code) {
    case KeyCode::KEY_APOSTROPHE:
        rk = ::KEY_APOSTROPHE;
        break;
    case KeyCode::KEY_COMMA:
        rk = ::KEY_COMMA;
        break;
    case KeyCode::KEY_MINUS:
        rk = ::KEY_MINUS;
        break;
    case KeyCode::KEY_PERIOD:
        rk = ::KEY_PERIOD;
        break;
    case KeyCode::KEY_SLASH:
        rk = ::KEY_SLASH;
        break;
    case KeyCode::KEY_ZERO:
        rk = ::KEY_ZERO;
        break;
    case KeyCode::KEY_ONE:
        rk = ::KEY_ONE;
        break;
    case KeyCode::KEY_TWO:
        rk = ::KEY_TWO;
        break;
    case KeyCode::KEY_THREE:
        rk = ::KEY_THREE;
        break;
    case KeyCode::KEY_FOUR:
        rk = ::KEY_FOUR;
        break;
    case KeyCode::KEY_FIVE:
        rk = ::KEY_FIVE;
        break;
    case KeyCode::KEY_SIX:
        rk = ::KEY_SIX;
        break;
    case KeyCode::KEY_SEVEN:
        rk = ::KEY_SEVEN;
        break;
    case KeyCode::KEY_EIGHT:
        rk = ::KEY_EIGHT;
        break;
    case KeyCode::KEY_NINE:
        rk = ::KEY_NINE;
        break;
    case KeyCode::KEY_SEMICOLON:
        rk = ::KEY_SEMICOLON;
        break;
    case KeyCode::KEY_EQUAL:
        rk = ::KEY_EQUAL;
        break;
    case KeyCode::KEY_A:
        rk = ::KEY_A;
        break;
    case KeyCode::KEY_B:
        rk = ::KEY_B;
        break;
    case KeyCode::KEY_C:
        rk = ::KEY_C;
        break;
    case KeyCode::KEY_D:
        rk = ::KEY_D;
        break;
    case KeyCode::KEY_E:
        rk = ::KEY_E;
        break;
    case KeyCode::KEY_F:
        rk = ::KEY_F;
        break;
    case KeyCode::KEY_G:
        rk = ::KEY_G;
        break;
    case KeyCode::KEY_H:
        rk = ::KEY_H;
        break;
    case KeyCode::KEY_I:
        rk = ::KEY_I;
        break;
    case KeyCode::KEY_J:
        rk = ::KEY_J;
        break;
    case KeyCode::KEY_K:
        rk = ::KEY_K;
        break;
    case KeyCode::KEY_L:
        rk = ::KEY_L;
        break;
    case KeyCode::KEY_M:
        rk = ::KEY_M;
        break;
    case KeyCode::KEY_N:
        rk = ::KEY_N;
        break;
    case KeyCode::KEY_O:
        rk = ::KEY_O;
        break;
    case KeyCode::KEY_P:
        rk = ::KEY_P;
        break;
    case KeyCode::KEY_Q:
        rk = ::KEY_Q;
        break;
    case KeyCode::KEY_R:
        rk = ::KEY_R;
        break;
    case KeyCode::KEY_S:
        rk = ::KEY_S;
        break;
    case KeyCode::KEY_T:
        rk = ::KEY_T;
        break;
    case KeyCode::KEY_U:
        rk = ::KEY_U;
        break;
    case KeyCode::KEY_V:
        rk = ::KEY_V;
        break;
    case KeyCode::KEY_W:
        rk = ::KEY_W;
        break;
    case KeyCode::KEY_X:
        rk = ::KEY_X;
        break;
    case KeyCode::KEY_Y:
        rk = ::KEY_Y;
        break;
    case KeyCode::KEY_Z:
        rk = ::KEY_Z;
        break;
    case KeyCode::KEY_LEFT_BRACKET:
        rk = ::KEY_LEFT_BRACKET;
        break;
    case KeyCode::KEY_BACKSLASH:
        rk = ::KEY_BACKSLASH;
        break;
    case KeyCode::KEY_RIGHT_BRACKET:
        rk = ::KEY_RIGHT_BRACKET;
        break;
    case KeyCode::KEY_GRAVE:
        rk = ::KEY_GRAVE;
        break;
    case KeyCode::KEY_SPACE:
        rk = ::KEY_SPACE;
        break;
    case KeyCode::KEY_ESCAPE:
        rk = ::KEY_ESCAPE;
        break;
    case KeyCode::KEY_ENTER:
        rk = ::KEY_ENTER;
        break;
    case KeyCode::KEY_TAB:
        rk = ::KEY_TAB;
        break;
    case KeyCode::KEY_BACKSPACE:
        rk = ::KEY_BACKSPACE;
        break;
    case KeyCode::KEY_INSERT:
        rk = ::KEY_INSERT;
        break;
    case KeyCode::KEY_DELETE:
        rk = ::KEY_DELETE;
        break;
    case KeyCode::KEY_RIGHT:
        rk = ::KEY_RIGHT;
        break;
    case KeyCode::KEY_LEFT:
        rk = ::KEY_LEFT;
        break;
    case KeyCode::KEY_DOWN:
        rk = ::KEY_DOWN;
        break;
    case KeyCode::KEY_UP:
        rk = ::KEY_UP;
        break;
    case KeyCode::KEY_PAGE_UP:
        rk = ::KEY_PAGE_UP;
        break;
    case KeyCode::KEY_PAGE_DOWN:
        rk = ::KEY_PAGE_DOWN;
        break;
    case KeyCode::KEY_HOME:
        rk = ::KEY_HOME;
        break;
    case KeyCode::KEY_END:
        rk = ::KEY_END;
        break;
    case KeyCode::KEY_CAPS_LOCK:
        rk = ::KEY_CAPS_LOCK;
        break;
    case KeyCode::KEY_SCROLL_LOCK:
        rk = ::KEY_SCROLL_LOCK;
        break;
    case KeyCode::KEY_NUM_LOCK:
        rk = ::KEY_NUM_LOCK;
        break;
    case KeyCode::KEY_PRINT_SCREEN:
        rk = ::KEY_PRINT_SCREEN;
        break;
    case KeyCode::KEY_PAUSE:
        rk = ::KEY_PAUSE;
        break;
    case KeyCode::KEY_F1:
        rk = ::KEY_F1;
        break;
    case KeyCode::KEY_F2:
        rk = ::KEY_F2;
        break;
    case KeyCode::KEY_F3:
        rk = ::KEY_F3;
        break;
    case KeyCode::KEY_F4:
        rk = ::KEY_F4;
        break;
    case KeyCode::KEY_F5:
        rk = ::KEY_F5;
        break;
    case KeyCode::KEY_F6:
        rk = ::KEY_F6;
        break;
    case KeyCode::KEY_F7:
        rk = ::KEY_F7;
        break;
    case KeyCode::KEY_F8:
        rk = ::KEY_F8;
        break;
    case KeyCode::KEY_F9:
        rk = ::KEY_F9;
        break;
    case KeyCode::KEY_F10:
        rk = ::KEY_F10;
        break;
    case KeyCode::KEY_F11:
        rk = ::KEY_F11;
        break;
    case KeyCode::KEY_F12:
        rk = ::KEY_F12;
        break;
    case KeyCode::KEY_LEFT_SHIFT:
        rk = ::KEY_LEFT_SHIFT;
        break;
    case KeyCode::KEY_LEFT_CONTROL:
        rk = ::KEY_LEFT_CONTROL;
        break;
    case KeyCode::KEY_LEFT_ALT:
        rk = ::KEY_LEFT_ALT;
        break;
    case KeyCode::KEY_LEFT_SUPER:
        rk = ::KEY_LEFT_SUPER;
        break;
    case KeyCode::KEY_RIGHT_SHIFT:
        rk = ::KEY_RIGHT_SHIFT;
        break;
    case KeyCode::KEY_RIGHT_CONTROL:
        rk = ::KEY_RIGHT_CONTROL;
        break;
    case KeyCode::KEY_RIGHT_ALT:
        rk = ::KEY_RIGHT_ALT;
        break;
    case KeyCode::KEY_RIGHT_SUPER:
        rk = ::KEY_RIGHT_SUPER;
        break;
    case KeyCode::KEY_KB_MENU:
        rk = ::KEY_KB_MENU;
        break;
    default:
        break;
    }
    return ::IsKeyDown(rk);
}
