#include "game_entity.h"

#include <iostream>
#include <assert.h>

#include "../graphics/sprite.h"

namespace GameLib {

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
GameEntity::GameEntity (void) :
	physical (nullptr),
	renderable (nullptr),
	anchor_type (ANCHOR_CENTER) {
}

// ------------------------------------------------------------
//
// ------------------------------------------------------------
GameEntity::~GameEntity (void) {
}

// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void GameEntity::Update (float dt) {

	// centers the entity based on anchor type
	if (renderable && physical) {
		anchor();
	}
}

// ------------------------------------------------------------
// Move
// ------------------------------------------------------------
void GameEntity::Move (float dx, float dy) {
	physical->position.x += dx;
	physical->position.y += dy;
}

// ------------------------------------------------------------
// SetPosition
// ------------------------------------------------------------
void GameEntity::SetPosition (float x, float y, float z) {

	assert (physical != nullptr);

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
			renderable->SetPosition (physical->position.x, physical->position.y);
			break;
		case ANCHOR_CENTER:
			renderable->SetPosition (physical->position.x - renderable->GetWidth() / 2, physical->position.y - renderable->GetHeight() / 2);
			break;
		case ANCHOR_BASELINE:
			renderable->SetPosition (physical->position.x - renderable->GetWidth() / 2, physical->position.y - renderable->GetHeight());
			break;
	}
}

}// GameLiib
