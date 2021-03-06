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
 * @file animation.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
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
    void SetSpeed(unsigned int speed);
    void IncSpeed();
    void DecSpeed();

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
    float ticks = 0;
};
} // GameLib
