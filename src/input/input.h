#pragma once

#include <SFML/System/Clock.hpp>

namespace GameLib {

/**
* @brief The input_event enum
*/
enum input_event { UP = 0, DOWN, LEFT, RIGHT, FIRE_DOWN, FIRE_UP, FIRE_LENGTH, FIRE_LENGTH_CACHED, SINGLE_TAP, float_TAP, FIRE_PRESS, TOTAL_EVENTS };

/**
 * @brief The Input class
 */
class Input {
  public:
    /**
     * @brief Input
     */
    Input();

    /**
     * @brief ~Input
     */
    virtual ~Input();

    /**
     * @brief Update
     */
    virtual void Update() = 0;

    /// event states
    int event_states[TOTAL_EVENTS];

  protected:
    sf::Clock fire_timer;

    /**
     * @brief reset
     */
    void Reset();
};

} // GameLib
