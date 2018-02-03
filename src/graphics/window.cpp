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
// constructor
// ------------------------------------------------------------
GameLib::Window::Window(const std::string &title, int x, int y, unsigned int w, unsigned int h, bool fullscreen) {
  // default style
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
  window.setPosition(sf::Vector2i(x, y));

  // testing force framerate
  window.setFramerateLimit(120);

  // vsync
  // window.setVerticalSyncEnabled (true);
}

// ------------------------------------------------------------
// destructor
// ------------------------------------------------------------
Window::~Window(void) {
  window.close();
}

// ------------------------------------------------------------
// PollEvent
// ------------------------------------------------------------
WindowEvent Window::PollEvent(void) {
  // sfml event
  sf::Event sfml_event;

  // GameLib event
  WindowEvent wnd_event;

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
      wnd_event.param = Keyboard::keys[sfml_event.key.code];
    }

    else if (sfml_event.type == sf::Event::MouseWheelMoved) {
      wnd_event.type = WINDOW_EVENT_MOUSE_WHEEL_MOVED;
      wnd_event.param = Converter::IntToString(sfml_event.mouseWheel.delta);
    }
  }

  return wnd_event;
}

// ------------------------------------------------------------
// Clear
// ------------------------------------------------------------
void Window::Clear(void) {
  window.clear(sf::Color(255, 255, 255, 255));
}

// ------------------------------------------------------------
// Present
// ------------------------------------------------------------
void Window::Present(void) {
  window.display();
}

// ------------------------------------------------------------
// IsOpen
// ------------------------------------------------------------
bool Window::IsOpen(void) {
  return window.isOpen();
}

// ------------------------------------------------------------
// ShowCursor
// ------------------------------------------------------------
void Window::ShowCursor() {
  window.setMouseCursorVisible(true);
}

// ------------------------------------------------------------
// HideCursor
// ------------------------------------------------------------
void Window::HideCursor() {
  window.setMouseCursorVisible(false);
}

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
void Window::Draw(Renderable &r) {
  window.draw(r.get());
}

// ------------------------------------------------------------
// Draw
// ------------------------------------------------------------
void Window::Draw(sf::Drawable &d) {
  window.draw(d);
}

// ------------------------------------------------------------
// Close
// ------------------------------------------------------------
void Window::Close() {
  window.close();
}

// ------------------------------------------------------------
// SetView
// ------------------------------------------------------------
void Window::SetView(sf::View view) {
  window.setView(view);
}

} // GameLib
