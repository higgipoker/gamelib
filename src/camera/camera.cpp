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
 * @file camera.cpp
 * @author Paul Higgins
 * @date 2018
 * @brief camera implementation
 */
#include "camera.h"
#include <iostream>
namespace GameLib {

const float zoom_step = 0.01f;
// ------------------------------------------------------------
// Follow
// ------------------------------------------------------------
void Camera::Follow(GameEntity *e) {
    following = e;
}

#define SPEED 50
// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void Camera::Update(float dt) {

    if (following) {
        Vector3 distance = following->physical->position - Vector3(view.getCenter().x, view.getCenter().y);
        float mag = distance.magnitude();
        physical->velocity = distance.normalised() * SPEED * dt * mag;
        physical->position += physical->velocity;
    }

    update_position();

    zoom();
}

// ------------------------------------------------------------
// update_position
// ------------------------------------------------------------
void Camera::update_position() {

    // check for min bounds
    if (physical->position.x - view.getSize().x / 2 < 0) {
        physical->position.x = view.getSize().x / 2;
    }

    if (physical->position.y - view.getSize().y / 2 < 0) {
        physical->position.y = view.getSize().y / 2;
    }

    // check for horizontal bounds
    if (physical->position.x + view.getSize().x / 2 > world.w) {
        physical->position.x = world.w - view.getSize().x / 2;
    }

    // check for vertical bounds
    if (physical->position.y + view.getSize().y / 2 > world.h) {
        physical->position.y = world.h - view.getSize().y / 2;
    }

    // set viewport with "physical->position" at center point
    view.setCenter(physical->position.x, physical->position.y);
}

// ------------------------------------------------------------
// zoom
// ------------------------------------------------------------
void Camera::zoom() {
    //
    // Zoom out
    //
    if (zooming > 0) {
        if (++zoom_steps > 20) {
            zoom_steps = 0;
            zooming = 0;
            return;
        }

        if (abs_zoom < 0.42f) {
            abs_zoom += zoom_step;
        }
    }

    //
    // Zoom in
    //
    else if (zooming < 0) {
        if (++zoom_steps > 30) {
            zoom_steps = 0;
            zooming = 0;
            return;
        }

        if (abs_zoom > -1.51f) {
            abs_zoom -= zoom_step;
        }
    }
}

} // GameLib
