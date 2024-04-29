//
// Created by angus.goucher on 4/18/2024.
//

#include <memory>
#include <vector>

#include "actor.h"

#include "game.h"
#include "game/gamer.h"

#include "lobby/button.h"
#include "lobby/nameentry.h"
#include "lobby/lobby.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

int main()
{
    net::Game* game = new net::Game({ .WindowWidth = 900, .WindowHeight = 600, .WindowTitle = "Hello" });

    net::State* gameState = game->NewState();
    gameState->AddActor(new net::Gamer());

    net::State* lobbyState = game->NewState();
    net::Button* button = new net::Button("Join Lobby", { 10, 70, 100, 30 });
    net::Button* startButton = new net::Button("Begin Game", { 160, 10, 200, 70 });
    net::NameEntry* entry = new net::NameEntry();
    net::Lobby* lobby = new net::Lobby(button, startButton, entry, gameState);
    lobbyState->AddActor(entry);
    lobbyState->AddActor(button);
    lobbyState->AddActor(startButton);
    lobbyState->AddActor(lobby);

    game->RunGame(lobbyState);

    return 0;
}