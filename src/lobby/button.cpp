//
// Created by angus.goucher on 4/26/2024.
//

#include "button.h"

#include <utility>

net::Button::Button(std::string text, net::Rectangle rect)
    : m_Text(std::move(text))
    , m_Rect(rect)
{
}

bool net::Button::HandleEvent(net::Event event)
{
    if (event.Type == EVENT_MOUSE_MOTION_EVENT) {
        m_MouseOver = m_Rect.ContainsPoint({ event.Data.AsMouseMotionEvent.X, event.Data.AsMouseMotionEvent.Y });
    }
    if (event.Type == EVENT_MOUSE_BUTTON_EVENT) {
        bool pressed = event.Data.AsMouseButtonEvent.Pressed;
        m_Clicked = m_MouseOver && event.Data.AsMouseButtonEvent.Button == MouseButton::LEFT && pressed;

        if (pressed && m_MouseOver) {
            m_Pressed = true;
            return true;
        }
    }
    return false;
}

void net::Button::PreUpdate(float deltaSeconds)
{
    m_Pressed = false;
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
    const char* text = m_Text.c_str();
    float textWidth = renderer->GetTextWidth(text, 10);
    float textHeight = renderer->GetTextHeight(text, 10);

    if (m_MouseOver) {
        renderer->DrawRectangle(m_Rect, C8BLUE);
        renderer->DrawText(text, 10, m_Rect.X + m_Rect.Width / 2.f - textWidth / 2.f, m_Rect.Y + m_Rect.Height / 2.f - textHeight / 2.f, C8WHITE);
    } else {
        renderer->DrawRectangleLines(m_Rect, C8BLUE);
        renderer->DrawText(text, 10, m_Rect.X + m_Rect.Width / 2.f - textWidth / 2.f, m_Rect.Y + m_Rect.Height / 2.f - textHeight / 2.f, C8BLUE);
    }
}
