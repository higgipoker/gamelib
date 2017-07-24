#include "camera.h"
#include <iostream>
namespace GameLib {

// ------------------------------------------------------------
// Follow
// ------------------------------------------------------------
void Camera::Follow (GameEntity *e) {
	following = e;
	view.zoom (1);
}

#define SPEED 5000
// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void Camera::Update (float dt) {

	if (following) {
		Vector3 distance = following->physical->position - Vector3 (view.getCenter().x, view.getCenter().y);
		double mag = distance.magnitude();

		if (mag > 1) {
			physical->velocity = distance.normalised() * SPEED * dt * (mag * 0.01f);
			physical->position += physical->velocity;
			update_position();
		}
	}
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

	// check for max bounds
	if (physical->position.x + view.getSize().x / 2 > world.w) {
		physical->position.x = world.w - view.getSize().x / 2;
	}
	if (physical->position.y + view.getSize().y / 2 > world.h) {
		physical->position.y = world.h - view.getSize().y / 2;
	}

	// set viewport with "physical->position" at center point
	view.setCenter (physical->position.x, physical->position.y);
}

// ------------------------------------------------------------
// Zoom
// ------------------------------------------------------------
void Camera::ZoomOut () {
	//if (zoom_clicks > -30) {
		--zoom_clicks;
		view.zoom (1.1);
	//}
}

// ------------------------------------------------------------
// Zoom
// ------------------------------------------------------------
void Camera::ZoomIn () {
	//if (zoom_clicks < 30) {
		++zoom_clicks;
		view.zoom (0.9);
	//}
}

}// GameLib

