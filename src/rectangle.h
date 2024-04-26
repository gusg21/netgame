//
// Created by angus.goucher on 4/26/2024.
//

#ifndef NETGAME_RECTANGLE_H
#define NETGAME_RECTANGLE_H

#include "vec2.h"

namespace net {
struct Rectangle {
    float X = 0.f, Y = 0.f, Width = 0.f, Height = 0.f;

    [[nodiscard]] bool ContainsPoint(Vec2 point) const { return point.X > X && point.X < X + Width && point.Y > Y && point.Y < Y + Height; };
};
}

#endif // NETGAME_RECTANGLE_H
