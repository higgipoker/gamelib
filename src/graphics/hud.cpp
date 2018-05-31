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
 * @file hud.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "hud.h"
namespace GameLib {

// ------------------------------------------------------------
// funcname
// ------------------------------------------------------------
Hud::Hud() {}

// ------------------------------------------------------------
// ~Hud
// ------------------------------------------------------------
Hud::~Hud() {}

// ------------------------------------------------------------
// Render
// ------------------------------------------------------------
void Hud::Render(Window &window) {

    // if root hud object is invisible, so are all children!
    if (!visible)
        return;

    // render this hud, then render children

    for (auto child : children) {
        child->Render(window);
    }
}

// ------------------------------------------------------------
// Send
// ------------------------------------------------------------
void Hud::Send(const std::string &msg, std::vector<int> params) {
    //
    // SET POSITION
    //
    if (msg.compare("setposition") == 0) {

        int x_difference = params[0] - static_cast<int>(GetPosition().x);
        int y_difference = params[1] - static_cast<int>(GetPosition().y);

        SetPosition(params[0], params[1]);
        for (auto child : children) {
            child->Move(x_difference, y_difference);
        }
    }

    //
    // Move
    //
    if (msg.compare("setposition") == 0) {

        Move(params[0], params[1]);
        for (auto child : children) {
            child->Move(params[0], params[1]);
        }
    }
}

// ------------------------------------------------------------
// Send
// ------------------------------------------------------------
void Hud::Send(const std::string &msg) {

    //
    // SHOW
    //
    if (msg.compare("show") == 0) {
        Show();
        for (auto child : children) {
            child->Show();
        }
    }

    //
    // HIDE
    //
    if (msg.compare("hide") == 0) {
        Hide();
        for (auto child : children) {
            child->Hide();
        }
    }
}

// ------------------------------------------------------------
// Hide
// ------------------------------------------------------------
void Hud::Hide() { visible = false; }
// ------------------------------------------------------------
// Show
// ------------------------------------------------------------
void Hud::Show() { visible = true; }

// ------------------------------------------------------------
// Send
// ------------------------------------------------------------
void Hud::Send(const std::string &msg, std::vector<std::string> params) {}

} // namespace GameLib
