//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_INPUT_H
#define NETGAME_INPUT_H

#include "eventqueue.h"

namespace net {
class Input {
public:
    Input() = default;

    void PostEvents(net::EventQueue* queue);
};
}

#endif