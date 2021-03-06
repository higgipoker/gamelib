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
 * @file camera.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "camera.h"
#include <iostream>
namespace GameLib {

// ------------------------------------------------------------
// Camera
// ------------------------------------------------------------
Camera::Camera() { following = nullptr; }

// ------------------------------------------------------------
// Init
// ------------------------------------------------------------
void Camera::Init(int width, int height) {
  setSize(width, height);
  setCenter(width / 2, height / 2);
}

// ------------------------------------------------------------
// SetWorldrect
// ------------------------------------------------------------
void Camera::SetWorldRect(const Rectangle &world_rect) { world = world_rect; }

// ------------------------------------------------------------
// Follow
// ------------------------------------------------------------
void Camera::Follow(GameEntity *e) { following = e; }

#define SPEED 2
// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void Camera::Update(float dt) {
  if (following) {
    Vector3 distance =
        following->physical.position - Vector3(getCenter().x, getCenter().y);
    float mag = distance.magnitude();
    physical.velocity = distance.normalised() * SPEED * dt * mag;
    physical.position += physical.velocity;
  }

  update_position();
  // Letterbox();
}

// ------------------------------------------------------------
// update_position
// ------------------------------------------------------------
void Camera::update_position() {
  // confine to world bounds
  sf::IntRect v = GetViewInWorld();

  // not too far left
  if (physical.position.x - v.width / 2 < 0) {
    physical.position.x = v.width / 2;
  }

  // not too far right
  if (physical.position.x + v.width / 2 > world.w) {
    physical.position.x = world.w - v.width / 2;
  }

  // not too far up
  if (physical.position.y - v.height / 2 < 0) {
    physical.position.y = v.height / 2;
  }

  // not too far down
  if (physical.position.y + v.height / 2 > world.h) {
    physical.position.y = world.h - v.height / 2;
  }

  setCenter(physical.position.x, physical.position.y);
}

// ------------------------------------------------------------
// UpdateSceneView
// ------------------------------------------------------------
void Camera::UpdateSceneView(int width, int height) {
  //  setViewport(
  //      sf::FloatRect(getViewport().left, getViewport().top, width, height));
}

// ------------------------------------------------------------
// SetOffset
// ------------------------------------------------------------
void Camera::Letterbox() {
  int window_width = getSize().x;
  int window_height = getSize().y;

  float window_ratio = window_width / static_cast<float>(window_height);
  float view_ratio = getSize().x / static_cast<float>(getSize().y);
  float size_x = 1;
  float size_y = 1;
  float pos_x = 0;
  float pos_y = 0;

  bool horizontal_spacing = true;
  if (window_ratio < view_ratio) horizontal_spacing = false;

  // If horizontal_spacing is true, the black bars will appear on the left and
  // right side. Otherwise, the black bars will appear on the top and bottom.

  if (horizontal_spacing) {
    size_x = view_ratio / window_ratio;
    pos_x = (1 - size_x) / 2.f;
  }

  else {
    size_y = window_ratio / view_ratio;
    pos_y = (1 - size_y) / 2.f;
  }

  setViewport(sf::FloatRect(pos_x, pos_y, size_x, size_y));
}

sf::IntRect Camera::GetViewInWorld() {
  int w = getSize().x * (getViewport().width);
  int h = getSize().y * (getViewport().height);
  int x = getCenter().x - w / 2;
  int y = getCenter().y - h / 2;

  sf::IntRect rect(x, y, w, h);
  return rect;
}

void Camera::OnWindowResized(int x, int y) {
//  setSize(x, y);
//  setCenter(x / 2, y / 2);
}

}  // namespace GameLib
