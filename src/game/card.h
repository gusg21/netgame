//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_CARD_H
#define NETGAME_CARD_H

#include "../actor.h"

namespace net {
enum class CardValue {
    A,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};

enum class CardSuit {
    HEARTS,
    DIAMONDS,
    SPADES,
    CLUBS
};

class Card : public Actor {
public:
    Card();
    Card(CardValue value, CardSuit suit);

    bool HandleEvent(net::Event event) override;
    void Update(float deltaSeconds) override;
    void Draw(net::Renderer* renderer) override;

    float GetX() { return m_X; }
    float GetY() { return m_Y; }
    void SetPosition(float x, float y);
    uint32_t GetValue() { return (uint32_t)m_Value; }
    void SetValue(uint32_t value);
    uint32_t GetId() { return m_Id; }
    void SetId(uint32_t id);

    net::Rectangle GetRectangle();
    bool IsReal() { return m_Id != 0; }
    bool IsIdle() { return !m_Dragging; }

    static net::Rectangle GetCardTexCoords(CardValue value, CardSuit suit);

private:
    Texture m_CardsTexture;

    CardValue m_Value = CardValue::EIGHT;
    CardSuit m_Suit = CardSuit::DIAMONDS;

    bool m_MouseOver = false;
    bool m_Dragging = false;

    float m_X = 0.f, m_Y = 0.f;
    uint32_t m_Id = 0;
};
}

#endif // NETGAME_CARD_H
