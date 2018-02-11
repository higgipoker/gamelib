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
 * @file window.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "../math/vector3.h"
#include "events.h"
#include "renderable.h"

namespace GameLib {

class Window {
  public:
    /**
     * @brief Window
     * @param title
     * @param x
     * @param y
     * @param w
     * @param h
     * @param fullscreen
     */
    explicit Window(const std::string &title, unsigned int x, unsigned int y,
                    unsigned int w, unsigned int h, bool fullscreen = false);

    /**
  * @brief destructor
  */
    ~Window();

    /**
     * @brief poll for window events
     */
    WindowEvent PollEvent(WindowEvent &wnd_event);

    /**
     * @brief clear window
     */
    void Clear();

    /**
     * @brief flip back buffer
     */
    void Present();

    /**
     * @brief is window still open
     */
    bool IsOpen();

    /**
     * @brief show cursor
     */
    void ShowCursor();

    /**
     * @brief hide cursor
     */
    void HideCursor();

    /**
     * @brief constructorset icon image
     * @param filename image file name
     */
    void SetIcon(const std::string &filename);

    /**
     * @brief draw a renderable object
     * @param r renderable object to draw
     */
    void Draw(Renderable &r);

    /**
     * @brief close the window
     */
    void Close();

    /**
     * @brief set the viewport
     * @param  v view to set
     */
    void SetView(sf::View v);

    // tmp for testing
    /**
     * @brief Draw
     * @param d
     */
    void Draw(sf::Drawable &d);

    /**
     * @brief get position of window
     */
    Vector3 GetPosition() {
        return Vector3(window.getPosition().x, window.getPosition().y);
    }

    /**
     * @brief get size of window
     */
    Vector3 GetSize() {
        return Vector3(window.getSize().x, window.getSize().y);
    }

    /**
     * @brief VSync
     * @param on
     */
    void VSync(bool on) { window.setVerticalSyncEnabled(on); }

    // lock framerate
    static const int FPS = 60;

  protected:
    /// sfml window
    sf::RenderWindow window;

    /// an image for the window icon
    sf::Image img_icon;

  public:
    // tmp
    friend class Primitives;
};

} // GameLib
