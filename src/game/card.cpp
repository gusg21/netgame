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
{
    // TODO: Remove raylib-specific code!
    m_CardsTexture = LoadTexture("assets/cards.png");
}

void net::Card::Update()
{
}

void net::Card::Draw(net::Renderer* renderer)
{
    // TODO: Remove raylib-specific code!
    DrawTextureRec(m_CardsTexture, GetCardTexCoords(m_Value, m_Suit), Vector2Zero(), WHITE);
}

Rectangle net::Card::GetCardTexCoords(net::CardValue value, net::CardSuit suit)
{
    return {
        ((float)value * CARD_WIDTH), ((float)suit * CARD_HEIGHT),
        CARD_WIDTH, CARD_HEIGHT
    };
}
