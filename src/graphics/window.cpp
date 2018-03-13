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
 * @file window.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "window.h"

#include <iostream>
#include <vector>

#include "../input/keyboard.h"
#include "../utils/converter.h"

namespace GameLib {

// ------------------------------------------------------------
// plain old function
// ------------------------------------------------------------
bool valid_videomode(unsigned int width, unsigned int height) {
    // get list of supported video modes
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

    // search forone that matched the requested width and height
    for (auto it = modes.begin(); it != modes.end(); ++it) {
        if ((*it).width == width && (*it).height == height) {
            return true;
        }
    }

    return false;
}

// ------------------------------------------------------------
// Window
// ------------------------------------------------------------
Window::Window(const std::string &title, unsigned int x, unsigned int y, unsigned int w,
               unsigned int h, bool fullscreen) {
    // default style
    // unsigned int window_style = sf::Style::Titlebar | sf::Style::Close;
    unsigned int window_style = sf::Style::Default;

    // if fullscreen, look for a compatible video mode
    if (fullscreen) {
        sf::VideoMode desktop_mode = sf::VideoMode::getDesktopMode();
        window_style = sf::Style::None;
        w = desktop_mode.width;
        h = desktop_mode.height;
        if (valid_videomode(w, h)) {
            window_style = sf::Style::Fullscreen;
        } else {
            std::cout << "No valid fullscreen mode for " << w << "x" << h << std::endl;
        }
    }

    // create new window with requested styles
    window.create(sf::VideoMode(w, h), title, window_style);

    // move to requested position
    window.setPosition(sf::Vector2i(static_cast<int>(x), static_cast<int>(y)));

    // testing force framerate (not needed when using "fixed timestep")
    //window.setFramerateLimit(FPS);
}

// ------------------------------------------------------------
// destructor
// ------------------------------------------------------------
Window::~Window(void) { window.close(); }

// ------------------------------------------------------------
// Clear
// ------------------------------------------------------------
void Window::Clear(void) { window.clear(sf::Color::Black); }

// ------------------------------------------------------------
// Present
// ------------------------------------------------------------
void Window::Present(void) { window.display(); }

// ------------------------------------------------------------
// IsOpen
// ------------------------------------------------------------
bool Window::IsOpen(void) { return window.isOpen(); }

// ------------------------------------------------------------
// ShowCursor
// ------------------------------------------------------------
void Window::ShowCursor() { window.setMouseCursorVisible(true); }

// ------------------------------------------------------------
// HideCursor
// ------------------------------------------------------------
void Window::HideCursor() { window.setMouseCursorVisible(false); }

// ------------------------------------------------------------
// SetIcon
// ------------------------------------------------------------
void Window::SetIcon(const std::string &filename) {
    img_icon.loadFromFile(filename);
    window.setIcon(img_icon.getSize().x, img_icon.getSize().y, img_icon.getPixelsPtr());
}

// ------------------------------------------------------------
// Draw
// ------------------------------------------------------------
void Window::Draw(Renderable &r) { window.draw(r.Get()); }

// ------------------------------------------------------------
// Draw
// ------------------------------------------------------------
void Window::Draw(sf::Drawable &d) { window.draw(d); }

// ------------------------------------------------------------
// Close
// ------------------------------------------------------------
void Window::Close() { window.close(); }

// ------------------------------------------------------------
// SetView
// ------------------------------------------------------------
void Window::SetView(sf::View view) { window.setView(view); }

// ------------------------------------------------------------
// PollEvent
// ------------------------------------------------------------
WindowEvent Window::PollEvent(WindowEvent &wnd_event) {
    // sfml event
    sf::Event sfml_event;

    // sfml polling
    while (window.pollEvent(sfml_event)) {
        // convert to genereic GameLib event
        if (sfml_event.type == sf::Event::Closed) {
            window.close();
            wnd_event.type = WINDOW_EVENT_CLOSE;
        }

        else if (sfml_event.type == sf::Event::MouseMoved) {
            wnd_event.type = WINDOW_EVENT_MOUSE_MOVED;
        }

        else if (sfml_event.type == sf::Event::MouseButtonPressed) {
            wnd_event.type = WINDOW_EVENT_MOUSE_CLICKED;
        }

        else if (sfml_event.type == sf::Event::EventType::KeyPressed) {
            wnd_event.type = WINDOW_EVENT_KEY_DOWN;
            wnd_event.params.push_back(Keyboard::keys[sfml_event.key.code]);
        }

        else if (sfml_event.type == sf::Event::MouseWheelMoved) {
            wnd_event.type = WINDOW_EVENT_MOUSE_WHEEL_MOVED;
            wnd_event.params.push_back(sfml_event.mouseWheel.delta);
        }

        else if (sfml_event.type == sf::Event::Resized) {
            // update the view to the new size of the window
            wnd_event.type = WINDOW_EVENT_RESIZED;
            wnd_event.params.push_back(static_cast<int>(sfml_event.size.width));
            wnd_event.params.push_back(static_cast<int>(sfml_event.size.height));
        }
    }

    return wnd_event;
}

// ------------------------------------------------------------
// ConvertMousePosition
// ------------------------------------------------------------
Point Window::GetMousePosition() {
    // get the current mouse position in the window
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

    // convert it to world coordinates
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

    // return it
    Point p(worldPos.x, worldPos.y);
    return p;
}

} // GameLib
