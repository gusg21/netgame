//
// Created by angus.goucher on 4/18/2024.
//

#include "card.h"
#include "raymath.h"

#define CARD_WIDTH 48.f
#define CARD_HEIGHT 64.f

net::Card::Card(net::CardValue value, net::CardSuit suit) : m_Value(value), m_Suit(suit) {
    m_cardsTexture = LoadTexture("assets/cards.png");
}

void net::Card::Update() {

}

void net::Card::Draw() {
    DrawTextureRec(m_cardsTexture, GetCardTexCoords(m_Value, m_Suit), Vector2Zero(), WHITE);
}

Rectangle net::Card::GetCardTexCoords(net::CardValue value, net::CardSuit suit) {
    return {
            ((float) value * CARD_WIDTH), ((float) suit * CARD_HEIGHT),
            CARD_WIDTH, CARD_HEIGHT
    };
}

