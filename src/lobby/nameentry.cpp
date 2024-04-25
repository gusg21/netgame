#include "nameentry.h"

#include "../state.h"

net::NameEntry::NameEntry()
    : Actor()
{
    // Clear name buffer
    memset(m_NameBuffer, 0, sizeof(m_NameBuffer));
}

bool net::NameEntry::HandleEvent(net::Event event)
{
    if (event.Type == EVENT_CHAR_EVENT) {
        char c = event.Data.AsCharEvent.Char;
        m_NameBuffer[m_NameBufferCursor] = c;
        m_NameBufferCursor++;
    }
    return false;
}

void net::NameEntry::Update()
{
    
}

void net::NameEntry::Draw(net::Renderer* renderer)
{
    renderer->DrawText(m_NameBuffer, 10, 50);
}
