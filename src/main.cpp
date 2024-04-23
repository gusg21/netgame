//
// Created by angus.goucher on 4/18/2024.
//

#include <raylib.h>
#include <raymath.h>
#include <memory>
#include <vector>

#include "actor.h"
#include "game/card.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello");

    Camera2D camera{
            .offset = {.x = WINDOW_WIDTH / 2.f, .y = WINDOW_HEIGHT / 2.f},
            .target = Vector2Zero(),
            .rotation = 0.f,
            .zoom = 2.f,
    };

    std::vector<std::unique_ptr<net::Actor>> actors{};
    actors.push_back(std::make_unique<net::Card>(net::CardValue::FIVE, net::CardSuit::CLUBS));

    while (!WindowShouldClose()) {
        // Updating
        for (auto &actor: actors) {
            actor->Update();
        }

        // Rendering
        BeginDrawing();
        {
            ClearBackground(Color(124, 194, 100, 255));

            BeginMode2D(camera);
            {
                for (auto &actor: actors) {
                    actor->Draw();
                }
            }
            EndMode2D();

            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    return 0;
}