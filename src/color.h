//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_COLOR_H
#define NETGAME_COLOR_H

#include <cstdint>

namespace net {
struct Color8 {
    uint8_t r, g, b, a;
};
} // namespace net

#define C8WHITE            \
    Color8                 \
    {                      \
        255, 255, 255, 255 \
    }
#define C8BLUE             \
    Color8                 \
    {                      \
        100, 110, 240, 255 \
    }
#define C8RED              \
    Color8                 \
    {                      \
        240, 110, 100, 255 \
    }

#endif // NETGAME_COLOR_H
