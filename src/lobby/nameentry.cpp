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
        return true;
    }
    if (event.Type == EVENT_KEY_EVENT) {
        uint32_t key = event.Data.AsKeyEvent.Key;
        if (key == KEY_BACKSPACE) {
            m_NameBufferCursor--;
            if (m_NameBufferCursor < 0) m_NameBufferCursor = 0;
            m_NameBuffer[m_NameBufferCursor] = 0x00;
        }
        return false;
    }

    return false;
}

void net::NameEntry::Update(float deltaSeconds)
{
    
}

void net::NameEntry::DrawUI(net::Renderer* renderer)
{
    renderer->DrawTextFormatted("Enter your name:", 10, 30, { 200, 80, 60, 255 });
    renderer->DrawTextFormatted(fmod(GetState()->GetElapsedTime(), 0.5f) > 0.25f ? "%s_" : "%s", 10, 50, { 255, 255, 255, 255 }, m_NameBuffer);
}
