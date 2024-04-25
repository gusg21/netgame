#include "eventqueue.h"

void net::EventQueue::PostEvent(Event event) { m_Queue.push_back(event); }

net::Event net::EventQueue::GetNextEvent()
{
    if (m_ReadHeadIndex >= m_Queue.size() || m_ReadHeadIndex < 0)
        return { .Type = EVENT_NONE };
    
    Event event = m_Queue[m_ReadHeadIndex];

    m_ReadHeadIndex++;

    return event;
}

void net::EventQueue::HandleThisEvent()
{
    m_Queue.erase(m_Queue.begin() + m_ReadHeadIndex);
}

void net::EventQueue::ResetEventReadHead()
{
    m_ReadHeadIndex = 0;
}
