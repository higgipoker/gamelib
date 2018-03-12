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
// ~Camera
// ------------------------------------------------------------
Camera::~Camera() {}

// ------------------------------------------------------------
// Init
// ------------------------------------------------------------
void Camera::Init(int width, int height) {
    viewport.SetSize(width, height);
    scene_view.setCenter(viewport.x + viewport.w / 2, viewport.y + viewport.h / 2);
    scene_view.setSize(viewport.w, viewport.h);
    hud_view.setCenter(width / 2, height / 2);
    Letterbox(width, height);
}

// ------------------------------------------------------------
// SetWorldrect
// ------------------------------------------------------------
void Camera::SetWorldRect(const Rectangle &world_rect) { world = world_rect; }

// ------------------------------------------------------------
// Follow
// ------------------------------------------------------------
void Camera::Follow(GameEntity *e) { following = e; }

#define SPEED 50
// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void Camera::Update(float dt) {

    if (following) {
        Vector3 distance = following->physical.position -
                           Vector3(viewport.GetCenter().x, viewport.GetCenter().y);
        float mag = distance.magnitude();
        physical.velocity = distance.normalised() * SPEED * dt * mag;
        physical.position += physical.velocity;
    }

    update_position();
}

// ------------------------------------------------------------
// update_position
// ------------------------------------------------------------
void Camera::update_position() {

    // check for min bounds
    if (physical.position.x - viewport.w / 2 < 0) {
        physical.position.x = viewport.w / 2;
    }

    if (physical.position.y - viewport.h / 2 < 0) {
        physical.position.y = viewport.h / 2;
    }

    // check for horizontal bounds
    if (physical.position.x + viewport.w / 2 > world.w) {
        physical.position.x = world.w - viewport.w / 2;
    }

    // check for vertical bounds
    if (physical.position.y + viewport.h / 2 > world.h) {
        physical.position.y = world.h - viewport.h / 2;
    }

    // set viewport with "physical.position" at center point
    viewport.SetCenter(physical.position.x, physical.position.y);
}

// ------------------------------------------------------------
// GetViewPort
// ------------------------------------------------------------
Rectangle &Camera::GetViewport() { return viewport; }

// ------------------------------------------------------------
// GetSceneView
// ------------------------------------------------------------
sf::View &Camera::GetSceneView() {
    scene_view.setSize(viewport.w, viewport.h);
    scene_view.setCenter(viewport.x + viewport.w / 2, viewport.y + viewport.h / 2);
    return scene_view;
}

// ------------------------------------------------------------
// GetHudView
// ------------------------------------------------------------
sf::View &Camera::GetHudView() {
    // hud view dimensions should match main camera view
    hud_view.setSize(viewport.w, viewport.h);
    return hud_view;
}

// ------------------------------------------------------------
// UpdateSceneView
// ------------------------------------------------------------
void Camera::UpdateSceneView(int width, int height) {
    viewport.SetSize(width, height);
    // scene_view.setSize(sf::Vector2f(width, height));
}

// ------------------------------------------------------------
// SetOffset
// ------------------------------------------------------------
void Camera::Letterbox(float window_width, float window_height) {
    float windowRatio = window_width / (float)window_height;
    float viewRatio = scene_view.getSize().x / (float)scene_view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right
    // side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    scene_view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
    hud_view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
}
} // GameLib
