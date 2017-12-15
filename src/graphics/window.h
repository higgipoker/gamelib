/*
 * window.h
 *
 *  Created on: Jun 10, 2017
 *      Author: higgi
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
   * @brief constructor
   * @param title window name to display
   * @param x position
   * @param y position
   * @param w size
   * @param h sizw
   * @param fullsscreen full screen toggle
   */
  Window(const std::string &title, unsigned int x, unsigned int y, unsigned int w, unsigned int h, bool fullsscreen = false);

  /**
   * @brief destructor
   */
  ~Window();

  /**
   * @brief poll for window events
   */
  WindowEvent PollEvent();

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
  void Draw(sf::Drawable &d);

  /**
   * @brief get position of window
   */
  inline Vector3 GetPosition() {
    return Vector3(window.getPosition().x, window.getPosition().y);
  }

  /**
   * @brief get size of window
   */
  inline Vector3 GetSize() {
    return Vector3(window.getSize().x, window.getSize().y);
  }

  /// sfml window
  sf::RenderWindow window;

protected:
  /// an image for the window icon
  sf::Image img_icon;
};

} // GameLib
