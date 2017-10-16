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
		double mag = distance.magnitude();
		physical->velocity = distance.normalised() * SPEED * dt * mag;
		physical->position += physical->velocity;
	}

	update_position();

	// ------------------------------------------------------------
	// Zoom out
	// ------------------------------------------------------------
	if (zooming > 0) {
		if (++zoom_steps > 20) {
			zoom_steps = 0;
			zooming = 0;
			return;
		}

		if (abs_zoom < 0.42f) {
			// view.zoom(1 + zoom_step);
			abs_zoom += zoom_step;
		}
	}

	// ------------------------------------------------------------
	// Zoom in
	// ------------------------------------------------------------
	else if (zooming < 0) {
		if (++zoom_steps > 30) {
			zoom_steps = 0;
			zooming = 0;
			return;
		}

		if (abs_zoom > -1.51f) {
			// view.zoom(1 - zoom_step);
			abs_zoom -= zoom_step;
		}
	}
}

// ------------------------------------------------------------
// update_physical->position
// ------------------------------------------------------------
void Camera::update_position() {

	// check for min bounds
	if (physical->position.x - view.getSize().x / 2 < 0) {
		physical->position.x = view.getSize().x / 2;
	}

	if (physical->position.y - view.getSize().y / 2 < 0) {
		physical->position.y = view.getSize().y / 2;
	}

	// check for max bounds
	if (physical->position.x + view.getSize().x / 2 > world.w) {
		physical->position.x = world.w - view.getSize().x / 2;
	}

	if (physical->position.y + view.getSize().y / 2 > world.h) {
		physical->position.y = world.h - view.getSize().y / 2;
	}

	// set viewport with "physical->position" at center point
	view.setCenter(physical->position.x, physical->position.y);
}

} // GameLib
