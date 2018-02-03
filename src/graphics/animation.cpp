#include "animation.h"
#include <iostream>
namespace GameLib {

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Animation::Animation (const std::string &id, float frametime, bool loopanim, int n, ...) : name (id), loop (loopanim), running (false), frame_time (frametime) {

    va_list vl;
    va_start (vl, n);
    for (int i = 0; i < n; i++) {
        int val = va_arg (vl, int);
        frames.push_back (val);
    }
    va_end (vl);

    current_frame = frames.begin();
}

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Animation::Animation (const std::string &id, float frametime, bool loopanim, std::vector<unsigned int> f)
    : name (id), frames (f), current_frame (frames.begin()), loop (loopanim), running (false), frame_time (frametime) {
}

// ------------------------------------------------------------
// Start
// ------------------------------------------------------------
void Animation::Start() {
    current_frame = frames.begin();
    timer.restart();
    running = true;
}

// ------------------------------------------------------------
// Step
// ------------------------------------------------------------
void Animation::Step() {
    if (running) {
        if (timer.getElapsedTime().asMilliseconds() > frame_time) {
            timer.restart();

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
void Animation::SetSpeed (int speed) {
    frame_time = speed;
}

} // GameLib
