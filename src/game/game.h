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
 * @file game.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once

#include "../camera/camera.h"
#include "../console/console.h"
#include "../graphics/renderable.h"
#include "../graphics/window.h"
#include "../input/keyboard.h"
#include "../input/mouse.h"
#include "../physics/physical.h"
#include "../utils/timer.h"
#include "game_entity.h"
#include <vector>

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
    Game(const std::string &gamename, unsigned int x, unsigned int y, unsigned int w,
         unsigned int h, bool fullscreen);

    /**
      * @brief destruct
      */
    virtual ~Game() {}

    /**
     * @brief OnStart
     */
    virtual void OnStart() { gamestep_timer.Start(); }

    /**
     * @brief Tick
     */
    virtual void Tick();

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

    /**
     * @brief workingDirectory
     * @return
     */
    std::string WorkingDirectory();

    /// game main window
    Window window;

    /// a camera
    Camera camera;

    /// mouse interface
    Mouse mouse;

    /// main loop control
    bool running = true;

  protected:
    /// game physical entities
    std::vector<GameEntity *> game_entities;

    /// hud entities
    std::vector<GameEntity *> hud_entities;

    /**
    * @brief Simulate
    * @param dt
    */
    void simulate();

    /**
     * @brief Render
     */
    void render();

    /**
    * @brief HandleInput
    */
    virtual void handle_input(WindowEvent &event);

    /**
     * @brief prepare_scene
     */
    virtual void prepare_scene();

    /**
     * @brief prepare_hud
     */
    virtual void prepare_hud();

    /**
     * @brief calc_fps
     */
    void calc_fps();

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
    Timer gamestep_timer;

    /// event for main loop
    GameLib::WindowEvent event;

    /// current frame tracker
    int game_frame = 0;

    /// fps stuff
    float fps = 0;
    float frames_this_second = 0;
    float lastTime = 0.0f;
    float fps_timer = 0.0f;
};

} // GameLib
