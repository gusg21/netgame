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
    void PreUpdate(float deltaSeconds) override;
    void Update(float deltaSeconds) override;
    void Draw(net::Renderer* renderer) override;
    void DrawUI(net::Renderer* renderer) override;

    [[nodiscard]] bool WasPressed() const { return m_Pressed; }

private:
    std::string m_Text;
    net::Rectangle m_Rect;

    bool m_MouseOver = false;
    bool m_Clicked = false;
    bool m_Pressed = false;
};
}


#endif // NETGAME_BUTTON_H
