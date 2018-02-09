/****************************************************************************
 * Copyright (C) 2018 by Paul Higgins
 *
 * This file is part of GameLib.
 *
 *   GameLib is free software: you can redistribute it and/or modify it
 *   under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   GameLib is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with GameLib. If not, see <http://www.gnu.org/licenses/>
 ****************************************************************************/
/**
 * @file console.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "console.h"

#include "../game/game.h"
#include "../graphics/color.h"
#include "../graphics/primitives.h"
#include "../utils/converter.h"
#include <iostream>
#include <sstream>

namespace GameLib {

const std::string PREFIX = "> ";
const std::string CURSOR = "_";
const unsigned int MAX_ECHO_SIZE = 500;

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Console::Console(Game *g) : GameEntity(new Physical(), this), height(200), text("fonts/terminus_bold.ttf", 20), cursor("fonts/terminus_bold.ttf", 20), game(g) {
    this->z_order++;
    hud = true;
    text.SetColor(Color(0, 255, 0, 255));
    cursor.SetColor(Color(0, 255, 0, 255));

    name = "console";
    visible = false;
    history_iterator = 0;

    timer.Start();
}

// ------------------------------------------------------------
// Destructor
// ------------------------------------------------------------
Console::~Console() {
    delete physical;
}

// ------------------------------------------------------------
// Render
// ------------------------------------------------------------
void Console::Render(Window &window) {
    if (!visible) {
        return;
    }

    //
    // draw background
    //
    Primitives::FillColor(Color(0, 0, 0, 255));
    Primitives::OutlineColor(Color(0, 0, 0, 255));
    Primitives::Rectangle(window, 0, 0, static_cast<unsigned int>(window.GetSize().x), height);

    Primitives::OutlineColor(Color(255, 255, 255, 255));
    // Primitives::DrawLine(window, Vector3(0, 10), Vector3(window.GetSize().x, 10), 3);

    //
    // draw history
    //
    unsigned int line_height = 22;
    unsigned int y = height;
    y -= line_height;
    //    for (auto it = history.rbegin(); it != history.rend(); ++it) {
    //        text.SetText(*it);
    //        y -= line_height;
    //        text.SetPosition(0, y);
    //        text.Render(window);
    //    }

    //
    // draw echo list
    //
    for (auto it = echo_list.rbegin(); it != echo_list.rend(); ++it) {
        text.SetText("* " + *it);
        y -= line_height;
        text.SetPosition(0, y);
        text.Render(window);
    }

    //
    // draw current line
    //
    text.SetText(PREFIX + current_line);
    text.SetPosition(0, height - line_height);
    text.Render(window);

    if (timer.GetTicks() > 500) {
        timer.Start();
        show_cursor = !show_cursor;
    }

    //
    // draw cursor
    //
    std::string cursor_text;
    if (show_cursor) {
        for (unsigned int i = 0; i < current_line.size() + PREFIX.size(); ++i) {
            cursor_text += " ";
        }
        cursor_text += CURSOR;
    }
    cursor.SetText(cursor_text);
    cursor.SetPosition(0, height - line_height);
    cursor.Render(window);
}

// ------------------------------------------------------------
// OnKey
// ------------------------------------------------------------
void Console::OnKey(std::string &character) {

    if (character == "tab" || character == "escape") {
        visible = !visible;
        return;
    }

    if (!visible) {
        return;
    }

    if (character == "return") {
        if (current_line.length()) {
            execute();
        }
        return;
    }

    if (character == "backspace") {
        if (current_line.length()) {
            current_line.pop_back();
        }
        return;
    }

    if (character == "up") {
        if (history.size()) {
            if (history_iterator > 0) {
                --history_iterator;
            } else {
                current_line = history[history_iterator];
            }
        }
        return;
    }

    if (character == "down") {
        if (history.size()) {
            if (++history_iterator >= history.size()) {
                history_iterator = static_cast<unsigned int>(history.size()) - 1;
            }
            current_line = history[history_iterator];
        }
        return;
    }

    if (character == "dash") {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
            character = "_";
        } else {
            character = "-";
        }
    }

    current_line += character;
}

// ------------------------------------------------------------
// execute
// ------------------------------------------------------------
void Console::execute() {

    std::vector<std::string> spl = Converter::Split(current_line);

    std::cout << "execute command: " << spl[0] << std::endl;

    history.push_back(current_line);
    history_iterator = static_cast<unsigned int>(history.size());
    current_line.clear();

    if (spl[0] == "echo") {
        if (spl.size() > 1) {
            echo_list.push_back(spl[1]);
        }
    }

    else {
        game->Call(spl);
    }
}

// ------------------------------------------------------------
// Echo
// ------------------------------------------------------------
void Console::Echo(const std::vector<std::string> &texts) {
    for (auto it = texts.begin(); it != texts.end(); ++it) {
        echo_list.push_back(*it);
        std::cout << "Console:Echo:: " << *it << std::endl;
    }

    if (echo_list.size() > MAX_ECHO_SIZE) {
        echo_list.clear();
    }
}

} // GameLib
