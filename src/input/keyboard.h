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
 * @file keyboard.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once
#include "input.h"
#include "keycodes.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <map>

namespace GameLib {

/**
* @brief The Keyboard class
*/
class Keyboard : public Input {

  public:
    /**
     * @brief Keyboard
     */
    Keyboard();

    /**
     * @brief Init without construction
     */
    static void Init();

    /**
     * @brief Update
     */
    virtual void Update() override;

    /**
     * @brief IsKeyPressed
     * @param codeC
     * @return
     */
    static bool IsKeyPressed(keycode code) {
        int sf_key = 0;

        for (auto key : keys) {
            if (key.second == code) {
                sf_key = key.first;
            }
        }

        return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(sf_key));
    }

    /// key codes
    static std::map<int, keycode> keys;

    /// key translations
    static std::map<keycode, char> translate;

    /// key translations when shift is pressed
    static std::map<keycode, char> translate_shifted;

  protected:
};

} // GameLib
