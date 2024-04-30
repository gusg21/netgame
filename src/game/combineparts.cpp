#include "combineparts.h"

static float RandFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

net::CombineParts::CombineParts(float x, float y)
    : m_Parts {}
{
    for (auto& part : m_Parts) {
        part.X = x + RandFloat(-10.f, 10.f);
        part.Y = y + RandFloat(-10.f, 10.f);

        part.VelX = x + RandFloat(-10.f, 10.f);
        part.VelY = y + RandFloat(-30.f, 0.f);

        part.Gravity = 10.f;
    }
}

bool net::CombineParts::HandleEvent(net::Event event)
{
    return false;
}

void net::CombineParts::Update(float deltaSeconds)
{
    for (auto& part : m_Parts) {
        part.VelY += part.Gravity * deltaSeconds;

        part.X += part.VelX * deltaSeconds;
        part.Y += part.VelY * deltaSeconds;
    }
}

void net::CombineParts::Draw(net::Renderer* renderer)
{
    for (auto& part : m_Parts) {
        renderer->DrawRectangle({ part.X, part.Y, 10, 10 }, C8RED);
    }
}
