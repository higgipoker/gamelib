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
Camera::Camera() : GameEntity(new Physical(), new Renderable()) {
    following = nullptr;
    name = "camera";
}

// ------------------------------------------------------------
// ~Camera
// ------------------------------------------------------------
Camera::~Camera() {
    delete physical;
    delete renderable;
}

// ------------------------------------------------------------
// SetWorldrect
// ------------------------------------------------------------
void Camera::SetWorldRect(const Rectangle &world_rect) {
    world = world_rect;
}

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
        Vector3 distance = following->physical->position - Vector3(viewport.GetCenter().x, viewport.GetCenter().y);
        float mag = distance.magnitude();
        physical->velocity = distance.normalised() * SPEED * dt * mag;
        physical->position += physical->velocity;
    }

    update_position();
}

// ------------------------------------------------------------
// update_position
// ------------------------------------------------------------
void Camera::update_position() {

    // check for min bounds
    if (physical->position.x - viewport.w / 2 < 0) {
        physical->position.x = viewport.w / 2;
    }

    if (physical->position.y - viewport.h / 2 < 0) {
        physical->position.y = viewport.h / 2;
    }

    // check for horizontal bounds
    if (physical->position.x + viewport.w / 2 > world.w) {
        physical->position.x = world.w - viewport.w / 2;
    }

    // check for vertical bounds
    if (physical->position.y + viewport.h / 2 > world.h) {
        physical->position.y = world.h - viewport.h / 2;
    }

    // set viewport with "physical->position" at center point
    viewport.SetCenter(physical->position.x, physical->position.y);
}

// ------------------------------------------------------------
// GetViewPort
// ------------------------------------------------------------
Rectangle &Camera::GetViewport() {
    return viewport;
}

// ------------------------------------------------------------
// GetSceneView
// ------------------------------------------------------------
sf::View &Camera::GetSceneView() {
    scene_view.setCenter(viewport.x + viewport.w / 2, viewport.y + viewport.h / 2);
    scene_view.setSize(viewport.w, viewport.h);
    return scene_view;
}

// ------------------------------------------------------------
// GetHudView
// ------------------------------------------------------------
sf::View &Camera::GetHudView() {
    // hud view dimensions should match main camera view
    hud_view.setSize(scene_view.getSize());
    hud_view.setCenter(sf::Vector2f(hud_view.getSize().x / 2, hud_view.getSize().y / 2));
    return hud_view;
}
} // GameLib
