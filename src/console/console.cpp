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
Console::Console(Game &g) : height(200), text("fonts/terminus_bold.ttf", 20), cursor("fonts/terminus_bold.ttf", 20), game(g) {
    this->z_order++;
    text.SetColor(Color(0, 255, 0, 255));
    cursor.SetColor(Color(0, 255, 0, 255));

    visible = false;
}

// ------------------------------------------------------------
// Destructor
// ------------------------------------------------------------
Console::~Console() {}

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
    Primitives::Rectangle(window, 0, 0, static_cast<unsigned int>(window.GetSize().w), height);
    Primitives::OutlineColor(Color(255, 255, 255, 255));

    unsigned int line_height = 22;
    unsigned int y = height - line_height;

    // combine lists
    std::vector<std::string> full;
    for (auto item : history) {
        full.push_back(item);
    }
    for (auto item : echo_list) {
        full.push_back(item);
    }

    //
    // draw history
    //
    int cnt = 0;
    for (auto it = full.rbegin(); it != full.rend(); ++it) {
        //        if (++count_lines >= lines) {
        //            break;
        //        }
        if (++cnt < echo_offset)
            continue;

        text.SetText(*it);
        y -= line_height;
        text.SetPosition(0, y);
        text.Render(window);
    }

    //
    // draw echo list
    //
    //
    //    for (auto it = echo_list.rbegin(); it != echo_list.rend(); ++it) {
    //        if (++cnt < echo_offset)
    //            continue;
    //        text.SetText("* " + *it);
    //        y -= line_height;
    //        text.SetPosition(0, y);
    //        text.Render(window);
    //    }

    //
    // draw current line
    //
    text.SetText(PREFIX + current_line);
    text.SetPosition(0, height - line_height);
    text.Render(window);

    if (++cursor_ticks > 30) {
        cursor_ticks = 0;
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
void Console::OnKey(keycode key) {

    if (key == KEY_TAB || key == KEY_ESC) {
        visible = !visible;
        return;
    }

    if (!visible) {
        return;
    }

    if (key == KEY_RETURN) {
        if (current_line.length()) {
            execute();
        }
        return;
    }

    if (key == KEY_BACKSPACE) {
        if (current_line.length()) {
            current_line.pop_back();
        }
        return;
    }

    if (key == KEY_UPARROW) {
        if (idx_history > 0) {
            current_line = history[static_cast<unsigned long>(--idx_history)];
        }
        return;
    }

    if (key == KEY_DOWNARROW) {
        if (static_cast<unsigned long>(idx_history) < history.size() - 1) {
            current_line = history[static_cast<unsigned long>(++idx_history)];
        }
        return;
    }

    if (key == KEY_PAGEUP) {
        if (++echo_offset > static_cast<int>(echo_list.size())) {
            --echo_offset;
        }
        return;
    }

    if (key == KEY_PAGEDOWN) {
        if (--echo_offset <= 0) {
            ++echo_offset;
        }
        return;
    }

    // is a standard character key
    if (key <= KEY_SPACE) {
        if (Keyboard::IsKeyPressed(KEY_LSHIFT) || Keyboard::IsKeyPressed(KEY_RSHIFT)) {
            current_line += Keyboard::translate_shifted[key];
        } else {
            current_line += Keyboard::translate[key];
        }
    } else if (key == KEY_LSHIFT || key == KEY_RSHIFT) {
        std::cout << "GameLib::Console::OnKey - Shift pressed" << std::endl;
    } else {
        std::cout << "GameLib::Console::OnKey - Unhandled key" << key << std::endl;
    }
}

// ------------------------------------------------------------
// execute
// ------------------------------------------------------------
void Console::execute() {

    std::vector<std::string> spl = Converter::Split(current_line);

    std::cout << "execute command: " << spl[0] << std::endl;

    game.Call(spl);

    history.push_back(current_line);
    idx_history = static_cast<int>(history.size());
    current_line.clear();
}

// ------------------------------------------------------------
// Echo
// ------------------------------------------------------------
void Console::Echo(const std::vector<std::string> &texts) {
    for (auto text : texts) {
        echo_list.push_back(text);
    }

    if (echo_list.size() > MAX_ECHO_SIZE) {
        echo_list.clear();
    }
}

// ------------------------------------------------------------
// SetHeight
// ------------------------------------------------------------
void Console::SetHeight(unsigned int h) { height = h; }

} // GameLib
