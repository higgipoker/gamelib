#pragma once

#include <stdarg.h>
#include <string>
#include <vector>

#include <SFML/System/Clock.hpp>

namespace GameLib {

/**
* @brief The Animation class
*/
class Animation {
  public:
    /**
    * @brief constructor with varialbe list
    * @param id animatin name
    * @param frametime timing
    * @param loopanim loop
    * @param n number of args
    * */
    Animation(const std::string &id, float frametime, bool loopanim, int n, ...);

    /**
    *  @brief constructor with varialbe vector
    * @param frametime timing
    * @param loopanim loop?
    * @param f frames list
    * */
    Animation(const std::string &id, float frametime, bool loopanim, std::vector<unsigned int> f);

    /**
    * @brief start the animation
    */
    void Start();

    /**
    * @brief step the animation (call each frame)
    */
    void Step();

    /**
    * @brief stop animation
    */
    void Stop();

    /**
     * @brief is the animation currently running
     */
    bool IsRunning() const;

    /**
     * @brief get the current anim frame
     */
    unsigned int CurrentFrame() const;

    /**
     * @brief manual alter timing
     * @param speed new speed
     */
    void SetSpeed(int speed);

    /// a name to identify the anmation
    std::string name;

  private:
    /// list of frame numbers
    std::vector<unsigned int> frames;

    /// point to current frame
    std::vector<unsigned int>::iterator current_frame;

    /// is a looping animation
    bool loop;

    /// animation is still running
    bool running;

    /// time of a frame
    float frame_time;

    /// frame timer
    sf::Clock timer;
};
} // GameLib
