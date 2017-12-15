#include "xbox_controller.h"
#include <SFML/Window/Joystick.hpp>
#include <map>
namespace GameLib {

/// map button id's to string identifiers
std::map<int, std::string> buttons{
  {0, "A"},
  {1, "B"},
  {2, "X"},
  {3, "Y"},
  {4, "LB"},
  {5, "RB"},
  {6, "LTRIGER"},
  {7, "RTRIGGER"},
  {8, "BACK"},
  {9, "START"},
  {10, "XBOX"},
  {11, "LCKICK"},
  {12, "RCLICK"},
  {13, "LEFT"},
  {14, "RIGHT"},
  {15, "UP"},
  {16, "DOWN"},
};

void XboxController::Update() {

  sf::Joystick::update();

  //if (A()) {
    for (int i = 0; i < 100; ++i) {
      if (sf::Joystick::isButtonPressed(sf_joystick_index, i)) {
        if (buttons.find(i) != buttons.end())
          std::cout << buttons[i] << std::endl;
//        else
//          std::cout << "unknown: " << i << std::endl;
      }
    }
  //}

  // fire button
  event_states[FIRE_UP] = 0;
  if (A() || B() || X() || Y()) {
    if (event_states[FIRE_DOWN] == 0) {
      fire_timer.restart();
      event_states[FIRE_DOWN] = 1;
    } else {
      event_states[FIRE_LENGTH] = fire_timer.getElapsedTime().asMilliseconds();
    }
  }

  else if (event_states[FIRE_DOWN] == 1) {
    event_states[FIRE_UP] = 1;
    event_states[FIRE_DOWN] = 0;
    event_states[FIRE_LENGTH_CACHED] = fire_timer.getElapsedTime().asMilliseconds();
    event_states[FIRE_LENGTH] = 0;
  }

  // directions
  event_states[UP] = event_states[DOWN] = event_states[LEFT] = event_states[RIGHT] = 0;

  if (Up()) {
    event_states[UP] = 1;
  }

  if (Down()) {
    event_states[DOWN] = 1;
  }

  if (Left()) {
    event_states[LEFT] = 1;
  }

  if (Right()) {
    event_states[RIGHT] = 1;
  }
}

//  static XboxController GetController() {
//    for (int j = 0; j < sf::Joystick::Count; j++) {
//      if (sf::Joystick::isConnected(j)) {
//        XboxController controller(j);
//        return controller;
//      }
//    }

//    // HACKXboxController controller(-1);
//    XboxController controller(0);
//    return controller;
//  }

bool XboxController::isConnected() {
  if (sf_joystick_index < 0 || sf_joystick_index > sf::Joystick::Count)
    return false;
  else
    return sf::Joystick::isConnected(sf_joystick_index);
}

bool XboxController::A() {
  return sf::Joystick::isButtonPressed(sf_joystick_index, 0);
}

bool XboxController::B() {
  return sf::Joystick::isButtonPressed(sf_joystick_index, 1);
}

bool XboxController::X() {
  return sf::Joystick::isButtonPressed(sf_joystick_index, 2);
}

bool XboxController::Y() {
  return sf::Joystick::isButtonPressed(sf_joystick_index, 3);
}

bool XboxController::LeftBumper() {
  return sf::Joystick::isButtonPressed(sf_joystick_index, 4);
}

bool XboxController::RightBumper() {
  return sf::Joystick::isButtonPressed(sf_joystick_index, 5);
}

bool XboxController::LeftTriggerPressed(){
  return sf::Joystick::isButtonPressed(sf_joystick_index, 6);
}

bool XboxController::RightTriggerPressed(){
  return sf::Joystick::isButtonPressed(sf_joystick_index, 7);
}

bool XboxController::Back() {
  return sf::Joystick::isButtonPressed(sf_joystick_index, 8);
}

bool XboxController::Start() {
  return sf::Joystick::isButtonPressed(sf_joystick_index, 9);
}

bool XboxController::XboxButton() {
  return sf::Joystick::isButtonPressed(sf_joystick_index, 10);
}

bool XboxController::LeftThumbstickClick() {
  return sf::Joystick::isButtonPressed(sf_joystick_index, 11);
}

bool XboxController::RightThumbstickClick() {
  return sf::Joystick::isButtonPressed(sf_joystick_index, 12);
}

bool XboxController::DpadLeft() {
  return sf::Joystick::isButtonPressed(sf_joystick_index, 13);
}

bool XboxController::DpadRight() {
  return sf::Joystick::isButtonPressed(sf_joystick_index, 14);
}

bool XboxController::DpadUp() {
  return sf::Joystick::isButtonPressed(sf_joystick_index, 15);
}

bool XboxController::DpadDown() {
  return sf::Joystick::isButtonPressed(sf_joystick_index, 16);
}

float XboxController::LeftTriggerValue() {
  return sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::Z);
}

float XboxController::RightTriggerValue() {
  return sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::R);
}

bool XboxController::LeftTrigger() {
  return LeftTriggerValue() > trigger_threshold;
}

bool XboxController::RightTrigger() {
  return RightTriggerValue() > trigger_threshold;
}

sf::Vector2f XboxController::LeftThumbstick() {
  return sf::Vector2f(sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::X), sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::Y));
}

sf::Vector2f XboxController::RightThumbstick() {
  return sf::Vector2f(sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::U), sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::V));
}

bool XboxController::Up() {
  return DpadUp() || LeftThumbstick().y < -thumbstick_threshold;
}

bool XboxController::Down() {
  return DpadDown() || LeftThumbstick().y > thumbstick_threshold;
}

bool XboxController::Left() {
  return DpadLeft() || LeftThumbstick().x < -thumbstick_threshold;
}

bool XboxController::Right() {
  return DpadRight() || LeftThumbstick().x > thumbstick_threshold;
}

} // namespace GameLib
