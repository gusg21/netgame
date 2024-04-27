//
// Created by angus.goucher on 4/18/2024.
//

#include <memory>
#include <vector>

#include "actor.h"
#include "game.h"
#include "game/card.h"
#include "lobby/button.h"
#include "lobby/nameentry.h"
#include "lobby/lobby.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

int main()
{
    net::Game* game = new net::Game({ .WindowWidth = 1600, .WindowHeight = 900, .WindowTitle = "Hello" });

    net::State* gameState = game->NewState();
    gameState->AddActor(new net::Card(net::CardValue::FIVE, net::CardSuit::CLUBS));

    net::State* lobbyState = game->NewState();
    net::Button* button = new net::Button("Hello", { 10, 70, 100, 30 });
    net::NameEntry* entry = new net::NameEntry();
    net::Lobby* lobby = new net::Lobby(button, entry);
    lobbyState->AddActor(entry);
    lobbyState->AddActor(button);
    lobbyState->AddActor(lobby);

    game->RunGame(lobbyState);

    return 0;
}