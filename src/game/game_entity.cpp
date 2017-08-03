#include "game_entity.h"

#include <assert.h>
#include <iostream>

#include "../graphics/sprite.h"

namespace GameLib {

std::set<std::string> GameEntity::entity_names;

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
GameEntity::GameEntity(void) : physical(nullptr), renderable(nullptr), anchor_type(ANCHOR_CENTER) {}

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
GameEntity::GameEntity(Physical *p) : physical(p), renderable(nullptr), anchor_type(ANCHOR_CENTER) {}

// ------------------------------------------------------------
//
// ------------------------------------------------------------
GameEntity::~GameEntity(void) {}

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

    if (z) {
        physical->position.z = z;
    }
}

// ------------------------------------------------------------
// anchor
// ------------------------------------------------------------
void GameEntity::anchor() {

    switch (anchor_type) {
    default:
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
void GameEntity::SetName(const std::string &name) {

    if (entity_names.find(name) == entity_names.end()) {
        entity_names.insert(name);
    } else {
        std::cout << "Could not set name" << std::endl;
    }
}

// ------------------------------------------------------------
// GetName
// ------------------------------------------------------------
std::string GameEntity::GetName() { return name; }

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
