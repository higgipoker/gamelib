/****************************************************************************
 * Copyright (C) 2018 by Paul higgins
 *
 * This file is part of GameLib.
 *
 *   Box is free software: you can redistribute it and/or modify it
 *   under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Box is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with GameLib. If not, see <http://www.gnu.org/licenses/>
 ****************************************************************************/
/**
 * @file game.h
 * @author Paul higgins
 * @date 2018
 * @brief game declaration
 */
#pragma once

#include <vector>

#include "../camera/camera.h"
#include "../console/console.h"
#include "../graphics/renderable.h"
#include "../graphics/window.h"
#include "../physics/physical.h"
#include "../utils/timer.h"
#include "game_entity.h"

namespace GameLib {

/**
 * @brief The Game class
 */
class Game {
  public:
    /**
    * @brief constructor
    * @param gamename name of game
    * @param x window x position
    * @param y window y position
    * @param w window width
    * @param h window height
    * @param fullscreen full screen or not
    */
    explicit Game(const std::string &gamename, unsigned int x, unsigned int y, unsigned int w, unsigned int h, bool fullscreen);

    /**
     * @brief ~Game
     */
    virtual ~Game() {
    }

    /**
    * @brief HandleInput
    */
    virtual void HandleInput(WindowEvent &event);

    /**
    * @brief Simulate
    * @param dt
    */
    void Simulate();

    /**
     * @brief Render
     */
    void Render();

    /**
    * @brief add a game entity
    * @param entity entity to add
    */
    void AddEntity(GameEntity &entity);

    /**
     * @brief get list of entity names
     */
    std::vector<std::string> GetEntityNames();

    /**
     * @brief get an entity based on id
     */
    GameEntity *GetEntity(const std::string &name);

    /**
     * @brief call a function
     * @param params list of params
     */
    void Call(std::vector<std::string> params);

    /**
     * @brief call a function
     * @param func function name
     * @param n number of params
     */
    void Call(std::string func, std::string n, ...);

    /// game main window
    Window window;

    /// a camera
    Camera camera;

    /// program workig directory
    std::string working_directory;

    /// main loop control
    bool running = true;

  protected:
    /// game physical entities
    std::vector<GameEntity *> game_entities;

    /// hud entities
    std::vector<GameEntity *> hud_entities;

    // non moving view for the hud
    sf::View hud_view;

    /**
     * @brief step the simulation
     * @param dt time delta
     */
    void step(float dt);

    /**
     * @brief helper to render the hud
     */
    void render_hud();

    /**
     * @brief on_mouse_click
     * @param x
     * @param y
     */
    virtual void on_mouse_click(float x, float y) = 0;

    /// console
    Console console;

    /// a timer
    Timer timer;

    /// fps stuff
    float fps;
    sf::Clock fps_clock;
    float lastTime = 0.0f;
};

} // GameLib
