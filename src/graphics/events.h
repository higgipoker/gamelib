#pragma once
#include <string>

namespace GameLib {

/** @brief list of window events */
enum event {
    WINDOW_EVENT_NONE,
    WINDOW_EVENT_CLOSE,
    WINDOW_EVENT_MOUSE_MOVED,
    WINDOW_EVENT_MOUSE_CLICKED,
    WINDOW_EVENT_MOUSE_WHEEL_MOVED,
    WINDOW_EVENT_KEY_DOWN
};

/** @brief event */
struct WindowEvent {

    /**
     * @brief constructor
     */
    WindowEvent (void) : type (WINDOW_EVENT_NONE) {
    }
    /// type
    event type;

    /// param
    std::string param;
};

} // GameLib
