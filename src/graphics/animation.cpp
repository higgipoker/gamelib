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
 * @file animation.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "animation.h"
#include <iostream>
namespace GameLib {

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Animation::Animation(const std::string &id, float frametime, bool loopanim, int n, ...) : name(id), loop(loopanim), running(false), frame_time(frametime) {

    va_list vl;
    va_start(vl, n);
    for (int i = 0; i < n; i++) {
        int val = va_arg(vl, int);
        frames.push_back(static_cast<unsigned int>(val));
    }
    va_end(vl);

    current_frame = frames.begin();
}

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Animation::Animation(const std::string &id, float frametime, bool loopanim, std::vector<unsigned int> f)
    : name(id), frames(f), current_frame(frames.begin()), loop(loopanim), running(false), frame_time(frametime) {
}

// ------------------------------------------------------------
// Start
// ------------------------------------------------------------
void Animation::Start() {
    current_frame = frames.begin();
    ticks = 0;
    running = true;
}

// ------------------------------------------------------------
// Step
// ------------------------------------------------------------
void Animation::Step() {
    if (running) {
        if (++ticks > frame_time) {
            ticks = 0;

            if (++current_frame == frames.end()) {
                if (loop) {
                    current_frame = frames.begin();
                } else {
                    running = false;
                    --current_frame;
                }
            }
        }
    }
}

// ------------------------------------------------------------
// Stop
// ------------------------------------------------------------
void Animation::Stop() {
    running = false;
}

// ------------------------------------------------------------
// IsRunning
// ------------------------------------------------------------
bool Animation::IsRunning() const {
    return running;
}

// ------------------------------------------------------------
// CurrentFrame
// ------------------------------------------------------------
unsigned int Animation::CurrentFrame() const {
    return *current_frame;
}

// ------------------------------------------------------------
// SetSpeed
// ------------------------------------------------------------
void Animation::SetSpeed(unsigned int speed) {
    frame_time = speed;
}

} // GameLib
