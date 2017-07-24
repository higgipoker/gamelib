#pragma once

#include <vector>

#include "game_entity.h"
#include "../graphics/window.h"
#include "../graphics/renderable.h"
#include "../physics/physical.h"
#include "../camera/camera.h"
#include "../console/console.h"
#include "../utils/timer.h"

namespace GameLib {

class Game {
public:

    /**
    * \brief constructor
    * \param gamename name of game
	* \param x window x position
	* \param y window y position
	* \param w window width
	* \param h window height
	* \param fullscreen full screen or not
    */
    explicit Game(const std::string &gamename, int x, int y, int w, int h, bool fullscreen);

    /**
     * \brief destructor
     */
    virtual ~Game(void);

    /**
    * \brief main game loop
    * \param dt time delta
    */
    void Loop(float dt);

    /**
    * \brief add a game entity
	* \param entity entity to add
    */
    void AddEntity(GameEntity &entity);

	/**
	 * \brief get list of entity names
	 */
	std::vector<std::string> GetEntityNames();

	/**
	 * \brief call a function
	 * \param func function name
	 */
	void Call(std::string func);

	/**
	 * \brief call a function
	 * \param func function name
	 * \param n number of params
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
    std::vector< GameEntity* > game_entities;

	/// hud entities
    std::vector< GameEntity* > hud_entities;

	// non moving view for the hud
	sf::View hud_view;

	/**
	 * \brief do rendering
	 */
	void render();

	/**
	 * \brief do physics
	 * \param dt physics step
	 */
	void physics(float dt);

	/**
	 * \brief keyboard handling
	 */
	void handle_keyboard();

	/// console
	Console console;

	/// a timer
	Timer timer;

	/// fps tracking
	void calc_fps();
	float fps;
	sf::Clock fps_clock;
	float lastTime = 0.0f;
};

}// GameLib