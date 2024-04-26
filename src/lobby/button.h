//
// Created by angus.goucher on 4/26/2024.
//

#ifndef NETGAME_BUTTON_H
#define NETGAME_BUTTON_H

#include "../actor.h"
#include "../rectangle.h"
namespace net {
class Button : public Actor {
public:
    explicit Button(std::string text, net::Rectangle rect);

    bool HandleEvent(net::Event event) override;
    void Update(float deltaSeconds) override;
    void Draw(net::Renderer* renderer) override;
    void DrawUI(net::Renderer* renderer) override;

private:
    std::string m_Text;
    bool m_MouseOver = false;
    net::Rectangle m_Rect;
};
}


#endif // NETGAME_BUTTON_H
