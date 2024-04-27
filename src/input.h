//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_INPUT_H
#define NETGAME_INPUT_H

#include <cstdint>
#include <assert.h>
#include <memory>

#define INPUT_KEY_COUNT 105

namespace net {
class EventQueue;

enum class KeyCode {
    KEY_APOSTROPHE, // Key: '
    KEY_COMMA, // Key: ,
    KEY_MINUS, // Key: -
    KEY_PERIOD, // Key: .
    KEY_SLASH, // Key: /
    KEY_ZERO, // Key: 0
    KEY_ONE, // Key: 1
    KEY_TWO, // Key: 2
    KEY_THREE, // Key: 3
    KEY_FOUR, // Key: 4
    KEY_FIVE, // Key: 5
    KEY_SIX, // Key: 6
    KEY_SEVEN, // Key: 7
    KEY_EIGHT, // Key: 8
    KEY_NINE, // Key: 9
    KEY_SEMICOLON, // Key: ;
    KEY_EQUAL, // Key: =
    KEY_A, // Key: A | a
    KEY_B, // Key: B | b
    KEY_C, // Key: C | c
    KEY_D, // Key: D | d
    KEY_E, // Key: E | e
    KEY_F, // Key: F | f
    KEY_G, // Key: G | g
    KEY_H, // Key: H | h
    KEY_I, // Key: I | i
    KEY_J, // Key: J | j
    KEY_K, // Key: K | k
    KEY_L, // Key: L | l
    KEY_M, // Key: M | m
    KEY_N, // Key: N | n
    KEY_O, // Key: O | o
    KEY_P, // Key: P | p
    KEY_Q, // Key: Q | q
    KEY_R, // Key: R | r
    KEY_S, // Key: S | s
    KEY_T, // Key: T | t
    KEY_U, // Key: U | u
    KEY_V, // Key: V | v
    KEY_W, // Key: W | w
    KEY_X, // Key: X | x
    KEY_Y, // Key: Y | y
    KEY_Z, // Key: Z | z
    KEY_LEFT_BRACKET, // Key: [
    KEY_BACKSLASH, // Key: '\'
    KEY_RIGHT_BRACKET, // Key: ]
    KEY_GRAVE, // Key: `
    // Function keys
    KEY_SPACE, // Key: Space
    KEY_ESCAPE, // Key: Esc
    KEY_ENTER, // Key: Enter
    KEY_TAB, // Key: Tab
    KEY_BACKSPACE, // Key: Backspace
    KEY_INSERT, // Key: Ins
    KEY_DELETE, // Key: Del
    KEY_RIGHT, // Key: Cursor right
    KEY_LEFT, // Key: Cursor left
    KEY_DOWN, // Key: Cursor down
    KEY_UP, // Key: Cursor up
    KEY_PAGE_UP, // Key: Page up
    KEY_PAGE_DOWN, // Key: Page down
    KEY_HOME, // Key: Home
    KEY_END, // Key: End
    KEY_CAPS_LOCK, // Key: Caps lock
    KEY_SCROLL_LOCK, // Key: Scroll down
    KEY_NUM_LOCK, // Key: Num lock
    KEY_PRINT_SCREEN, // Key: Print screen
    KEY_PAUSE, // Key: Pause
    KEY_F1, // Key: F1
    KEY_F2, // Key: F2
    KEY_F3, // Key: F3
    KEY_F4, // Key: F4
    KEY_F5, // Key: F5
    KEY_F6, // Key: F6
    KEY_F7, // Key: F7
    KEY_F8, // Key: F8
    KEY_F9, // Key: F9
    KEY_F10, // Key: F10
    KEY_F11, // Key: F11
    KEY_F12, // Key: F12
    KEY_LEFT_SHIFT, // Key: Shift left
    KEY_LEFT_CONTROL, // Key: Control left
    KEY_LEFT_ALT, // Key: Alt left
    KEY_LEFT_SUPER, // Key: Super left
    KEY_RIGHT_SHIFT, // Key: Shift right
    KEY_RIGHT_CONTROL, // Key: Control right
    KEY_RIGHT_ALT, // Key: Alt right
    KEY_RIGHT_SUPER, // Key: Super right
    KEY_KB_MENU, // Key: KB menu
    // Keypad keys
    KEY_KP_0, // Key: Keypad 0
    KEY_KP_1, // Key: Keypad 1
    KEY_KP_2, // Key: Keypad 2
    KEY_KP_3, // Key: Keypad 3
    KEY_KP_4, // Key: Keypad 4
    KEY_KP_5, // Key: Keypad 5
    KEY_KP_6, // Key: Keypad 6
    KEY_KP_7, // Key: Keypad 7
    KEY_KP_8, // Key: Keypad 8
    KEY_KP_9, // Key: Keypad 9
    KEY_KP_DECIMAL, // Key: Keypad .
    KEY_KP_DIVIDE, // Key: Keypad /
    KEY_KP_MULTIPLY, // Key: Keypad *
    KEY_KP_SUBTRACT, // Key: Keypad -
    KEY_KP_ADD, // Key: Keypad +
    KEY_KP_ENTER, // Key: Keypad Enter
    KEY_KP_EQUAL, // Key: Keypad =
    KEY_COUNT
};

enum class MouseButton {
    LEFT, RIGHT, MIDDLE // Infurating ordering
};

class Input {
public:
    Input() {
        assert((int)net::KeyCode::KEY_COUNT == INPUT_KEY_COUNT);
        memset(m_PrevKeys, false, INPUT_KEY_COUNT);
    };

    void PostEvents(net::EventQueue* queue);

    bool IsKeyDown(net::KeyCode code);

private:

    bool m_PrevKeys[INPUT_KEY_COUNT];
};
}

#endif