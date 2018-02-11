/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
/**
 * @file keyboard.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "keyboard.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

namespace GameLib {

std::map<int, keycode> Keyboard::keys;
std::map<keycode, char> Keyboard::translate;
std::map<keycode, char> Keyboard::translate_shifted;
// ------------------------------------------------------------
// Keyboard
// ------------------------------------------------------------
Keyboard::Keyboard() {
    Init();
}

// ------------------------------------------------------------
// init
// ------------------------------------------------------------
void Keyboard::Init() {
    keys.clear();
    int code = 0;
    keys.insert(std::make_pair(code++, KEY_A));
    keys.insert(std::make_pair(code++, KEY_B));
    keys.insert(std::make_pair(code++, KEY_C));
    keys.insert(std::make_pair(code++, KEY_D));
    keys.insert(std::make_pair(code++, KEY_E));
    keys.insert(std::make_pair(code++, KEY_F));
    keys.insert(std::make_pair(code++, KEY_G));
    keys.insert(std::make_pair(code++, KEY_H));
    keys.insert(std::make_pair(code++, KEY_I));
    keys.insert(std::make_pair(code++, KEY_J));
    keys.insert(std::make_pair(code++, KEY_K));
    keys.insert(std::make_pair(code++, KEY_L));
    keys.insert(std::make_pair(code++, KEY_M));
    keys.insert(std::make_pair(code++, KEY_N));
    keys.insert(std::make_pair(code++, KEY_O));
    keys.insert(std::make_pair(code++, KEY_P));
    keys.insert(std::make_pair(code++, KEY_Q));
    keys.insert(std::make_pair(code++, KEY_R));
    keys.insert(std::make_pair(code++, KEY_S));
    keys.insert(std::make_pair(code++, KEY_T));
    keys.insert(std::make_pair(code++, KEY_U));
    keys.insert(std::make_pair(code++, KEY_V));
    keys.insert(std::make_pair(code++, KEY_W));
    keys.insert(std::make_pair(code++, KEY_X));
    keys.insert(std::make_pair(code++, KEY_Y));
    keys.insert(std::make_pair(code++, KEY_Z));

    code = 26;
    keys.insert(std::make_pair(code++, KEY_0));
    keys.insert(std::make_pair(code++, KEY_1));
    keys.insert(std::make_pair(code++, KEY_2));
    keys.insert(std::make_pair(code++, KEY_3));
    keys.insert(std::make_pair(code++, KEY_4));
    keys.insert(std::make_pair(code++, KEY_5));
    keys.insert(std::make_pair(code++, KEY_6));
    keys.insert(std::make_pair(code++, KEY_7));
    keys.insert(std::make_pair(code++, KEY_8));
    keys.insert(std::make_pair(code++, KEY_9));
    keys.insert(std::make_pair(code++, KEY_ESC));
    keys.insert(std::make_pair(57, KEY_SPACE));
    keys.insert(std::make_pair(58, KEY_RETURN));
    keys.insert(std::make_pair(60, KEY_TAB));
    keys.insert(std::make_pair(59, KEY_BACKSPACE));
    keys.insert(std::make_pair(73, KEY_UPARROW));
    keys.insert(std::make_pair(74, KEY_DOWNARROW));
    keys.insert(std::make_pair(38, KEY_LSHIFT));
    keys.insert(std::make_pair(42, KEY_RSHIFT));
    keys.insert(std::make_pair(56, KEY_MINUS));
    keys.insert(std::make_pair(61, KEY_PAGEUP));
    keys.insert(std::make_pair(62, KEY_PAGEDOWN));

    translate.insert(std::make_pair(KEY_A, 'a'));
    translate.insert(std::make_pair(KEY_B, 'b'));
    translate.insert(std::make_pair(KEY_C, 'c'));
    translate.insert(std::make_pair(KEY_D, 'd'));
    translate.insert(std::make_pair(KEY_E, 'e'));
    translate.insert(std::make_pair(KEY_F, 'f'));
    translate.insert(std::make_pair(KEY_G, 'g'));
    translate.insert(std::make_pair(KEY_H, 'h'));
    translate.insert(std::make_pair(KEY_I, 'i'));
    translate.insert(std::make_pair(KEY_J, 'j'));
    translate.insert(std::make_pair(KEY_K, 'k'));
    translate.insert(std::make_pair(KEY_L, 'l'));
    translate.insert(std::make_pair(KEY_M, 'm'));
    translate.insert(std::make_pair(KEY_N, 'n'));
    translate.insert(std::make_pair(KEY_O, 'o'));
    translate.insert(std::make_pair(KEY_P, 'p'));
    translate.insert(std::make_pair(KEY_Q, 'q'));
    translate.insert(std::make_pair(KEY_R, 'r'));
    translate.insert(std::make_pair(KEY_S, 's'));
    translate.insert(std::make_pair(KEY_T, 't'));
    translate.insert(std::make_pair(KEY_U, 'u'));
    translate.insert(std::make_pair(KEY_V, 'v'));
    translate.insert(std::make_pair(KEY_W, 'w'));
    translate.insert(std::make_pair(KEY_X, 'x'));
    translate.insert(std::make_pair(KEY_Y, 'y'));
    translate.insert(std::make_pair(KEY_Z, 'z'));
    translate.insert(std::make_pair(KEY_0, '0'));
    translate.insert(std::make_pair(KEY_1, '1'));
    translate.insert(std::make_pair(KEY_2, '2'));
    translate.insert(std::make_pair(KEY_3, '3'));
    translate.insert(std::make_pair(KEY_4, '4'));
    translate.insert(std::make_pair(KEY_5, '5'));
    translate.insert(std::make_pair(KEY_6, '6'));
    translate.insert(std::make_pair(KEY_7, '7'));
    translate.insert(std::make_pair(KEY_8, '8'));
    translate.insert(std::make_pair(KEY_9, '9'));
    translate.insert(std::make_pair(KEY_SPACE, ' '));

    translate_shifted.insert(std::make_pair(KEY_A, 'A'));
    translate_shifted.insert(std::make_pair(KEY_B, 'B'));
    translate_shifted.insert(std::make_pair(KEY_C, 'C'));
    translate_shifted.insert(std::make_pair(KEY_D, 'D'));
    translate_shifted.insert(std::make_pair(KEY_E, 'E'));
    translate_shifted.insert(std::make_pair(KEY_F, 'F'));
    translate_shifted.insert(std::make_pair(KEY_G, 'G'));
    translate_shifted.insert(std::make_pair(KEY_H, 'H'));
    translate_shifted.insert(std::make_pair(KEY_I, 'I'));
    translate_shifted.insert(std::make_pair(KEY_J, 'J'));
    translate_shifted.insert(std::make_pair(KEY_K, 'K'));
    translate_shifted.insert(std::make_pair(KEY_L, 'L'));
    translate_shifted.insert(std::make_pair(KEY_M, 'M'));
    translate_shifted.insert(std::make_pair(KEY_N, 'N'));
    translate_shifted.insert(std::make_pair(KEY_O, 'O'));
    translate_shifted.insert(std::make_pair(KEY_P, 'P'));
    translate_shifted.insert(std::make_pair(KEY_Q, 'Q'));
    translate_shifted.insert(std::make_pair(KEY_R, 'R'));
    translate_shifted.insert(std::make_pair(KEY_S, 'S'));
    translate_shifted.insert(std::make_pair(KEY_T, 'T'));
    translate_shifted.insert(std::make_pair(KEY_U, 'U'));
    translate_shifted.insert(std::make_pair(KEY_V, 'V'));
    translate_shifted.insert(std::make_pair(KEY_W, 'W'));
    translate_shifted.insert(std::make_pair(KEY_X, 'X'));
    translate_shifted.insert(std::make_pair(KEY_Y, 'Y'));
    translate_shifted.insert(std::make_pair(KEY_Z, 'Z'));
    translate_shifted.insert(std::make_pair(KEY_0, ')'));
    translate_shifted.insert(std::make_pair(KEY_1, '!'));
    translate_shifted.insert(std::make_pair(KEY_2, '\"'));
    translate_shifted.insert(std::make_pair(KEY_3, '3'));
    translate_shifted.insert(std::make_pair(KEY_4, '$'));
    translate_shifted.insert(std::make_pair(KEY_5, '%'));
    translate_shifted.insert(std::make_pair(KEY_6, '^'));
    translate_shifted.insert(std::make_pair(KEY_7, '&'));
    translate_shifted.insert(std::make_pair(KEY_8, '*'));
    translate_shifted.insert(std::make_pair(KEY_9, '('));
}

// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void Keyboard::Update() {
    event_states[FIRE_UP] = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        event_states[UP] = 1;
    } else {
        event_states[UP] = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        event_states[DOWN] = 1;
    } else {
        event_states[DOWN] = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        event_states[LEFT] = 1;
    } else {
        event_states[LEFT] = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        event_states[RIGHT] = 1;
    } else {
        event_states[RIGHT] = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        if (event_states[FIRE_DOWN] == 0) {
            fire_timer.restart();
            event_states[FIRE_DOWN] = 1;
        } else {
            event_states[FIRE_LENGTH] = fire_timer.getElapsedTime().asMilliseconds();
        }
    } else if (event_states[FIRE_DOWN] == 1) {
        event_states[FIRE_UP] = 1;
        event_states[FIRE_DOWN] = 0;
        event_states[FIRE_LENGTH_CACHED] = fire_timer.getElapsedTime().asMilliseconds();
        event_states[FIRE_LENGTH] = 0;
    }
}

} // GameLib
