//
// Created by angus.goucher on 4/18/2024.
//

#include "card.h"

#include "../renderer.h"
#include "../game.h"

#define CARD_WIDTH 48.f
#define CARD_HEIGHT 64.f

net::Card::Card()
    : m_CardsTexture("assets/cards.png")
{
    m_Suit = (net::CardSuit)(rand() % 4);
}

net::Card::Card(net::CardValue value, net::CardSuit suit)
    : m_Value(value)
    , m_Suit(suit)
    , m_CardsTexture("assets/cards.png")
{
}

bool net::Card::HandleEvent(net::Event event)
{
    if (event.Type == EVENT_MOUSE_MOTION_EVENT) {
        net::Vec2 mousePos = { event.Data.AsMouseMotionEvent.X, event.Data.AsMouseMotionEvent.Y };
        net::Vec2 worldPos = GetGame()->GetRenderer()->ScreenToWorld(mousePos);

        if (!m_Dragging) {
            if (GetRectangle().ContainsPoint(worldPos)) {
                m_MouseOver = true;
            } else {
                m_MouseOver = false;
            }
        } else {
            m_MouseOver = false;
            m_X = worldPos.X - CARD_WIDTH / 2.f;
            m_Y = worldPos.Y - CARD_HEIGHT / 2.f;
        }
        
    }
    if (event.Type == EVENT_MOUSE_BUTTON_EVENT) {
        if (m_MouseOver && event.Data.AsMouseButtonEvent.Button == MouseButton::LEFT && event.Data.AsMouseButtonEvent.Pressed) {
            char cardId = m_Id;
            GetGame()->GetNetworker()->SendServerEvent({ .EventType = NET_SERVER_PICK_UP_CARD, .Data = { cardId } });
            return true;
        }
        if (m_Dragging && event.Data.AsMouseButtonEvent.Button == MouseButton::LEFT && !event.Data.AsMouseButtonEvent.Pressed) {
            char cardId = m_Id;
            GetGame()->GetNetworker()->SendServerEvent({ .EventType = NET_SERVER_PUT_DOWN_CARD, .Data = { cardId } });
            return true;
        }
    }
    if (event.Type == EVENT_ALLOW_CARD_MOVE_EVENT) {
        if (event.Data.AsAllowCardMoveEvent.CardId == m_Id && !m_Dragging) {
            m_Dragging = true;
            return true;
        }
    }
    if (event.Type == EVENT_FINISH_CARD_MOVE_EVENT) {
        if (event.Data.AsFinishCardMoveEvent.CardId == m_Id && m_Dragging) {
            m_Dragging = false;
            return true;
        }
    }
    return false;
}

void net::Card::Update(float deltaSeconds)
{
    if (m_Dragging && GetState()->GetFrameNumber() % 50 == 1) {
        // Update server
        struct MoveCardEventData {
            uint32_t Id;
            float X, Y;
        };

        net::ServerEvent event {};
        MoveCardEventData data
        {
            .Id = m_Id,
            .X = m_X,
            .Y = m_Y
        };
        event.EventType = NET_SERVER_MOVE_CARD;
        memcpy(event.Data, &data, sizeof(MoveCardEventData));
        GetGame()->GetNetworker()->SendServerEvent(event);
    }
}

void net::Card::Draw(net::Renderer* renderer)
{
    if (IsReal()) {
        renderer->DrawTextureRec(m_CardsTexture, GetCardTexCoords(m_Value, m_Suit), m_X, m_Y, C8WHITE);
        if (m_MouseOver) {
            renderer->DrawRectangleLines(GetRectangle(), C8RED);
        }
    }
}

void net::Card::SetPosition(float x, float y)
{
    m_X = x;
    m_Y = y;
}

void net::Card::SetValue(uint32_t value)
{
    m_Value = (CardValue)value;
}

void net::Card::SetId(uint32_t id)
{
    m_Id = id;
}

net::Rectangle net::Card::GetRectangle()
{
    return {
        m_X, m_Y, CARD_WIDTH, CARD_HEIGHT
    };
}

net::Rectangle net::Card::GetCardTexCoords(net::CardValue value, net::CardSuit suit)
{
    return {
        ((float)value * CARD_WIDTH), ((float)suit * CARD_HEIGHT),
        CARD_WIDTH, CARD_HEIGHT
    };
}
