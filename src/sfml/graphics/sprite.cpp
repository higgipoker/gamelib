#include "sprite.h"

namespace GameLib {

// ------------------------------------------------------------------
// Constructor
// ------------------------------------------------------------------
Sprite::Sprite (const std::string &filename, unsigned int num_rows, unsigned int num_cols) : Renderable (filename),
	current_animation (nullptr) {

	// set the size of each sprite in the sheet
	sprite_width  = texture->getSize().x / num_cols;
	sprite_height = texture->getSize().y / num_rows;

	// set up the coordinates of each frame
	for (int row = 0; row < num_rows; row++) {
		for (int col = 0; col < num_cols; col++) {

			// a rect struct
			sf::IntRect rect;

			// sprite rectangle
			rect.left 		= col * sprite_width;
			rect.top 		= row * sprite_height;
			rect.width 		= sprite_width;
			rect.height 	= sprite_height;

			// add rect to list
			rects.push_back (rect);
		}
	}
}

// ------------------------------------------------------------------
// SetFrame
// ------------------------------------------------------------------
void Sprite::SetFrame (unsigned int frame) {
	sprite.setTextureRect (rects.at (frame));
}

// ------------------------------------------------------------------
// AddAnimation
// ------------------------------------------------------------------
void Sprite::AddAnimation (const std::string &animname, float frametime, bool loopanim, std::vector<int> framelist) {
	AddAnimation (Animation (animname, frametime, loopanim, framelist));
}

// ------------------------------------------------------------------
// AddAnimation
// ------------------------------------------------------------------
void Sprite::AddAnimation (Animation anim) {

	// add new animation to the list
	animations.push_back (anim);

	// set the current animation to the newly added one
	current_animation = &animations.back();

	// auto start
	current_animation->Start();
}

// ------------------------------------------------------------------
// Animate
// ------------------------------------------------------------------
void Sprite::Animate() {
	if (current_animation) {
		current_animation->Step();
		SetFrame (current_animation->CurrentFrame());
	}
	if (shadow) {
		shadow->Animate();
	}
}

// ------------------------------------------------------------------
// Move
// ------------------------------------------------------------------
void Sprite::Move (float dx, float dy) {
	Renderable::Move (dx, dy);
	sprite.setPosition (geometry.x, geometry.y);
}

// ------------------------------------------------------------------
// SetAnimation
// ------------------------------------------------------------------
void Sprite::SetAnimation (const std::string &name) {
	if (current_animation && current_animation->name == name) return;

	for (std::vector<Animation>::iterator it = animations.begin(); it != animations.end(); ++it) {

		if ( (*it).name == name) {
			current_animation = & (*it);
			current_animation->Start();
			break;
		}
	}
}

// ------------------------------------------------------------------
// Scale
// ------------------------------------------------------------------
void Sprite::Scale (float x_factor, float y_factor) {
	sprite.setScale (x_factor, y_factor);
}

// ------------------------------------------------------------------
// Scale
// ------------------------------------------------------------------
void Sprite::Scale (float factor) {
	sprite.setScale (factor, factor);
}

// ------------------------------------------------------------------
// SetAnimationSpeed
// ------------------------------------------------------------------
void Sprite::SetAnimationSpeed (int time) {
	if (current_animation) {
		current_animation->SetSpeed (time);
	}
}
}// GameLib
