//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_CARD_H
#define NETGAME_CARD_H

#include <raylib.h>

#include "../actor.h"

namespace net {
    enum class CardValue {
        A, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
    };

    enum class CardSuit {
        HEARTS, DIAMONDS, SPADES, CLUBS
    };

    class Card : public Actor {
    public:
        Card(CardValue value, CardSuit suit);

        void Update() override;
        void Draw() override;

        static Rectangle GetCardTexCoords(CardValue value, CardSuit suit);

    private:
        Texture2D m_cardsTexture = {};

        CardValue m_Value;
        CardSuit m_Suit;
    };
}



#endif //NETGAME_CARD_H