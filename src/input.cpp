#include "input.h"
#include "raymath.h"

#include <raylib.h>

void net::Input::PostEvents(net::EventQueue* queue)
{
    int32_t keyCode = ::GetCharPressed();
    while (keyCode > 0) {
        bool readable = (keyCode >= 32) && (keyCode <= 125);
        if (readable || keyCode == 0x08) { // 0x08 = backspace
            queue->PostEvent(Event {
                .Type = EVENT_CHAR_EVENT,
                .Data = { .AsCharEvent = CharEvent { .Char = (char)keyCode } } });
        }

        keyCode = ::GetCharPressed();
    }

    keyCode = ::GetKeyPressed();
    while (keyCode > 0) {
        queue->PostEvent(Event {
            .Type = EVENT_KEY_EVENT,
            .Data = { .AsKeyEvent = KeyEvent { .Key = (uint32_t)keyCode } } });

        keyCode = ::GetKeyPressed();
    }

    Vector2 mouseDelta = ::GetMouseDelta();
    if (::Vector2Length(mouseDelta) > 0.f) {
        Vector2 mousePosition = ::GetMousePosition();
        queue->PostEvent(Event {
            .Type = EVENT_MOUSE_MOTION_EVENT,
            .Data = { .AsMouseMotionEvent = {
                          .DeltaX = mouseDelta.x, .DeltaY = mouseDelta.y, .X = mousePosition.x, .Y = mousePosition.y } } });
    }
}