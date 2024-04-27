//
// Created by angus.goucher on 4/18/2024.
//

#include "card.h"

#include <raymath.h>

#include "../renderer.h"

#define CARD_WIDTH 48.f
#define CARD_HEIGHT 64.f

net::Card::Card(net::CardValue value, net::CardSuit suit)
    : m_Value(value)
    , m_Suit(suit)
    , m_CardsTexture("assets/cards.png")
{
}

void net::Card::Update(float deltaSeconds)
{
}

void net::Card::Draw(net::Renderer* renderer)
{
    // TODO: Remove raylib-specific code!
    renderer->DrawTextureRec(m_CardsTexture, GetCardTexCoords(m_Value, m_Suit), 0.f, 0.f, C8WHITE);
}

net::Rectangle net::Card::GetCardTexCoords(net::CardValue value, net::CardSuit suit)
{
    return {
        ((float)value * CARD_WIDTH), ((float)suit * CARD_HEIGHT),
        CARD_WIDTH, CARD_HEIGHT
    };
}
