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
    virtual ~Game();

    /**
    * @brief Simulate
    * @param dt
    */
    void Simulate();

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
     * @brief step
     * @param dt
     */
    void step(float dt);

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
