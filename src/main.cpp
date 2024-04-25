//
// Created by angus.goucher on 4/18/2024.
//

#include <memory>
#include <vector>

#include "actor.h"
#include "game.h"
#include "game/card.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

int main()
{
    net::Game game({ .WindowWidth = 1600, .WindowHeight = 900, .WindowTitle = "Hello" });

    net::State* initialState = game.NewState();
    initialState->AddActor(new net::Card(net::CardValue::FIVE, net::CardSuit::CLUBS));

    game.RunGame(initialState);

    return 0;
}