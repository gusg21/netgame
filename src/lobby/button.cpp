//
// Created by angus.goucher on 4/26/2024.
//

#include "button.h"

#include <utility>

net::Button::Button(std::string text, net::Rectangle rect)
    : m_Text(std::move(text)), m_Rect(rect)
{
}

bool net::Button::HandleEvent(net::Event event)
{
    if (event.Type == EVENT_MOUSE_MOTION_EVENT) {
        m_MouseOver = m_Rect.ContainsPoint({ event.Data.AsMouseMotionEvent.X, event.Data.AsMouseMotionEvent.Y });
    }
    return false;
}

void net::Button::Update(float deltaSeconds)
{
    Actor::Update(deltaSeconds);
}

void net::Button::Draw(net::Renderer* renderer)
{
    Actor::Draw(renderer);
}

void net::Button::DrawUI(net::Renderer* renderer)
{
    const char* text = m_MouseOver ? "OVER" : "AWAY";
    float textWidth = 20.f;

    renderer->DrawText(text, m_Rect.X + m_Rect.Width / 2.f - textWidth / 2.f, m_Rect.Y + m_Rect.Height / 2.f - 5.f, { 100, 110, 240, 255 });
}
