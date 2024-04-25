#include "input.h"

#include <raylib.h>

void net::Input::PostEvents(net::EventQueue* queue)
{
    int32_t keyCode = GetCharPressed();
    while (keyCode > 0) {
        if ((keyCode >= 32) && (keyCode <= 125)) {
            queue->PostEvent(Event {
                .Type = EVENT_CHAR_EVENT,
                .Data = { .AsCharEvent = CharEvent { .Char = (char)keyCode } } });
        }

        keyCode = GetCharPressed();
    }
}