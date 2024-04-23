//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_ACTOR_H
#define NETGAME_ACTOR_H

#include <iostream>

namespace net {
    class Actor {
    public:
        ~Actor() { std::cout << "Actor Destroyed" << std::endl; }

        virtual void Update() = 0;
        virtual void Draw() = 0;
    };
}

#endif //NETGAME_ACTOR_H
