//
// Created by angus.goucher on 4/18/2024.
//

#include <raylib.h>
#include <raymath.h>
#include <memory>
#include <vector>

#include "actor.h"
#include "game/card.h"
#include "game.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

int main() {
    net::Game game(
        {
            .WindowWidth = 1600,
            .WindowHeight = 900,
            .WindowTitle = "Hello"
        }
    );

    net::State* initialState = game.NewState();
    initialState->AddActor(std::make_shared<net::Card>(net::CardValue::FIVE, net::CardSuit::CLUBS));

    game.RunGame(initialState);

    return 0;
}