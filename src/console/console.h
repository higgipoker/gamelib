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
 * @file console.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once

#include "../game/game_entity.h"
#include "../graphics/renderable.h"
#include "../graphics/text.h"
#include "../input/keycodes.h"
#include "../utils/timer.h"

namespace GameLib {
class Game;
class Console : public GameEntity, public Renderable {
  public:
    /**
     * @brief construct
     */
    explicit Console(Game *g);

    /**
      @brief destruct
     */
    ~Console();

    /**
    * @brief render
    * @param window render target
    */
    virtual void Render(Window &window) override;

    /**
     * @brief key press
     * @param character the char pressed
     */
    void OnKey(keycode key);

    /**
     * @brief echo something
     * @param texts strings to echo
     */
    void Echo(const std::vector<std::string> &texts);

  private:
    // console height
    unsigned int height;

    /// text renderable
    Label text;

    /// cursor
    Label cursor;

    /// current text
    std::string current_line;

    /// command history
    std::vector<std::string> history;

    /// track current history pointer
    int idx_history = 0;

    /// an echo list
    std::vector<std::string> echo_list;

    /// track echo offset
    int echo_offset = 1;

    /// pointer to game for function calls
    Game *game;

    /// a timer
    int cursor_ticks;

    /**
     * @brief render the cursor
     */
    bool show_cursor = false;

    /**
     * @brief execute the current command
     */
    void execute();
};

} // GameLib
