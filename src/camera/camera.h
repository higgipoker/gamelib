/****************************************************************************
 * Copyright (C) 2018 by Paul Higgins
 *
 * This file is part of GameLib.
 *
 *   Box is free software: you can redistribute it and/or modify it
 *   under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Box is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with GameLib. If not, see <http://www.gnu.org/licenses/>
 ****************************************************************************/
/**
 * @file camera.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once

#include "../game/game_entity.h"
#include "../math/shapes.h"
#include <SFML/Graphics.hpp>

namespace GameLib {

class Camera : public GameEntity {
  public:
    /**
    * @brief Camera
    */
    Camera() : GameEntity(new Physical(), new Renderable()) {
        following = nullptr;
        name = "camera";
        zoom_steps = 0;
        zooming = 0;
    }

    /**
     */
    ~Camera() {
        delete physical;
        delete renderable;
    }

    /**
     * @brief the main update function for an entity
     * @param dt time delta
     */
    virtual void Update(float dt) override;

    /**
     * @brief set up the game world rect
     * @param world_rect rectangle
     */
    inline void SetWorldRect(const Rectangle &world_rect) {
        world = world_rect;
    }

    /**
     * @brief follow a game entity
     * @param e game entity to follow
     */
    void Follow(GameEntity *e);

    /**
     * @brief get the current viewport
     */
    inline Rectangle GetViewport() {
        return Rectangle(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2, view.getSize().x, view.getSize().y);
    }

    /**
     * @brief zoom the camera
     */
    void ZoomOut() {
        zooming = 1;
    }

    /**
     * @brief zoom the camera
     */
    void ZoomIn() {
        zooming = -1;
    }

    float abs_zoom = 0;

    // tmp
    sf::View &GetView() {
        return view;
    }

  protected:
    // TODO
    sf::View view;

    /// whole game world
    Rectangle world;

    /// only move camera if target outside this Rectangle
    Rectangle anchor_rect;

    /// track which entity we are following
    GameEntity *following;

    /// track zooming
    int zoom_steps;
    int zooming;

    /**
     * @brief helper to update position
     */
    void update_position();

    /**
     * @brief zoom
     */
    void zoom();
};

} // GameLib
