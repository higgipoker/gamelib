/****************************************************************************
 * Copyright (C) 2018 by Paul Higgins
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
 * @file timer.h
 * @author Paul Higgins
 * @date 2018
 * @brief timer header file
 */
#pragma once
#include <SFML/System.hpp>

namespace GameLib {

/**
* @brief The Timer class
*/
class Timer {
  public:
    /**
     * @brief Start
     */
    void Start() {
        clock.restart();
    }

    /**
     * @brief GetTicks
     * @return
     */
    float GetTicks() {
        return clock.getElapsedTime().asMilliseconds();
    }

  protected:
    /// sfml implementation
    sf::Clock clock;
};

} // GameLib
