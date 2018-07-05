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
 * @file camera.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once

#include <SFML/Graphics/View.hpp>

// tmp
#include "../graphics/renderable.h"

#include "../game/game_entity.h"
#include "../math/shapes.h"

namespace GameLib {

/**
 * @brief The Camera class
 */
class Camera : public sf::View {
 public:
  /**
   * @brief Camera
   */
  explicit Camera();

  /**
   * @brief Init
   */
  void Init(int width, int height);

  /**
   * @brief the main update function for an entity
   * @param dt time delta
   */
  void Update(float dt);

  /**
   * @brief set up the game world rect
   * @param world_rect rectangle
   */
  void SetWorldRect(const Rectangle &world_rect);

  /**
   * @brief follow a game entity
   * @param e game entity to follow
   */
  void Follow(GameEntity *e);

  /**
   * @brief UpdateSceneView eg window resized
   */
  void UpdateSceneView(int width, int height);

  /**
   * @brief for maintain aspect ratio on window resize
   * @param x
   * @param y
   */
  void Letterbox();

  /**
   * @brief sf::Rect::GetViewInWorld
   */
  sf::IntRect GetViewInWorld();

  /**
   * @brief OnWindowResized
   * @param x
   * @param y
   */
  void OnWindowResized(int x, int y);

 protected:
  /// physical object for moving camera
  Physical physical;

  /// whole game world
  Rectangle world;

  /// track which entity we are following
  GameEntity *following;

  /**
   * @brief helper to update position
   */
  void update_position();
};

}  // namespace GameLib
