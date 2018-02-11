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
 * @file game_entity.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "game_entity.h"

#include <assert.h>
#include <iostream>

#include "../graphics/sprite.h"

namespace GameLib {

std::set<std::string> GameEntity::entity_names;

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
// GameEntity::GameEntity(void) : physical(nullptr), renderable(nullptr),
// velocity(physical->velocity), anchor_type(ANCHOR_CENTER) {
//}

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
GameEntity::GameEntity(Physical *p, Renderable *r) : physical(p), renderable(r), velocity(physical->velocity), anchor_type(ANCHOR_CENTER) {
}

// ------------------------------------------------------------
//
// ------------------------------------------------------------
GameEntity::~GameEntity(void) {
}

// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void GameEntity::Update(float dt) {

    // centers the entity based on anchor type
    if (renderable && physical) {
        anchor();
    }
}

// ------------------------------------------------------------
// Move
// ------------------------------------------------------------
void GameEntity::Move(float dx, float dy) {
    physical->position.x += dx;
    physical->position.y += dy;
}

// ------------------------------------------------------------
// SetPosition
// ------------------------------------------------------------
void GameEntity::SetPosition(float x, float y, float z) {

    assert(physical != nullptr);

    physical->position.x = x;
    physical->position.y = y;

    if (z > TOL) {
        physical->position.z = z;
    }
}

Point GameEntity::GetPosition() {
    return Point(physical->position.x, physical->position.y);
}

// ------------------------------------------------------------
// anchor
// ------------------------------------------------------------
void GameEntity::anchor() {

    switch (anchor_type) {

        case ANCHOR_NONE:
            renderable->SetPosition(physical->position.x, physical->position.y);
            break;
        case ANCHOR_CENTER:
            renderable->SetPosition(physical->position.x - renderable->GetWidth() / 2, physical->position.y - renderable->GetHeight() / 2);
            break;
        case ANCHOR_BASELINE:
            renderable->SetPosition(physical->position.x - renderable->GetWidth() / 2, physical->position.y - renderable->GetHeight());
            break;
    }
}

// ------------------------------------------------------------
// SetName
// ------------------------------------------------------------
void GameEntity::SetName(const std::string &n) {
    name = n;
    if (entity_names.find(name) == entity_names.end()) {
        entity_names.insert(name);
    } else {
        std::cout << "Could not set name: " << name << std::endl;
    }
}

// ------------------------------------------------------------
// GetName
// ------------------------------------------------------------
std::string GameEntity::GetName() {
    return name;
}

// ------------------------------------------------------------
// Call
// ------------------------------------------------------------
void GameEntity::Call(std::vector<std::string> params) {
    if (params[0] == "move") {
        std::vector<std::string> new_params(params.begin() + 1, params.end());
        SetPosition(atoi(new_params[0].c_str()), atoi(new_params[1].c_str()), atoi(new_params[2].c_str()));
    }
}

} // GameLiib
