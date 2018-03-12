#pragma once
#include <string>
#include <vector>

namespace GameLib {

/** @brief list of window events */
enum event {
    WINDOW_EVENT_NONE,
    WINDOW_EVENT_CLOSE,
    WINDOW_EVENT_MOUSE_MOVED,
    WINDOW_EVENT_MOUSE_CLICKED,
    WINDOW_EVENT_MOUSE_WHEEL_MOVED,
    WINDOW_EVENT_KEY_DOWN,
    WINDOW_EVENT_RESIZED,
};

/** @brief event */
struct WindowEvent {

    /**
     * @brief constructor
     */
    WindowEvent(void) : type(WINDOW_EVENT_NONE) {}

    /**
     * @brief Reset
     */
    void Reset() {
        type = WINDOW_EVENT_NONE;
        params.clear();
    }
    /// type
    event type;

    /// param
    std::vector<int> params;
};

} // GameLib
