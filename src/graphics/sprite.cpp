#include "sprite.h"
#include <iostream>
namespace GameLib {

// ------------------------------------------------------------------
// Constructor
// ------------------------------------------------------------------
Sprite::Sprite(const std::string &filename, unsigned int num_rows, unsigned int num_cols) : Renderable(filename), current_animation(nullptr), shadow(nullptr) {

  // set the size of each sprite in the sheet
  sprite_width = texture->getSize().x / num_cols;
  sprite_height = texture->getSize().y / num_rows;

  // set up the coordinates of each frame
  for (unsigned int row = 0; row < num_rows; row++) {
    for (unsigned int col = 0; col < num_cols; col++) {

      // sprite rectangle
      sf::IntRect rect;
      rect.left = int(col * sprite_width);
      rect.top = int(row * sprite_height);
      rect.width = int(sprite_width);
      rect.height = int(sprite_height);
      rects.push_back(rect);
    }
  }
}

Sprite::~Sprite() {
}

void Sprite::Render(Window &window) {
  // shadow gets drawn first
  if (shadow) {
    shadow->Render(window);
  }
  Renderable::Render(window);
}

// ------------------------------------------------------------------
// SetFrame
// ------------------------------------------------------------------
void Sprite::SetFrame(unsigned int frame) {
  sprite.setTextureRect(rects.at(frame));
}

// ------------------------------------------------------------------
// AddAnimation
// ------------------------------------------------------------------
void Sprite::AddAnimation(const std::string &animname, float frametime, bool loopanim, std::vector<unsigned int> framelist) {
  AddAnimation(Animation(animname, frametime, loopanim, framelist));
}

// ------------------------------------------------------------------
// AddAnimation
// ------------------------------------------------------------------
void Sprite::AddAnimation(Animation anim) {

  // add new animation to the list
  animations.push_back(anim);

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
    SetFrame(current_animation->CurrentFrame());
  }

  if (shadow) {
    shadow->Animate();
  }
}

// ------------------------------------------------------------------
// Move
// ------------------------------------------------------------------
void Sprite::Move(float dx, float dy) {
  Renderable::Move(dx, dy);
  sprite.setPosition(geometry.x, geometry.y);
}

// ------------------------------------------------------------------
// SetAnimation
// ------------------------------------------------------------------
void Sprite::SetAnimation(const std::string &name) {
  if (current_animation && current_animation->name == name)
    return;

  for (auto it = animations.begin(); it != animations.end(); ++it) {
    if ((*it).name == name) {
      current_animation = &(*it);
      current_animation->Start();
      break;
    }
  }

  if (shadow) {
    shadow->SetAnimation(name);
  }
}

// ------------------------------------------------------------------
// Scale
// ------------------------------------------------------------------
void Sprite::Scale(float x_factor, float y_factor) {
  sprite.setScale(x_factor, y_factor);
}

// ------------------------------------------------------------------
// Scale
// ------------------------------------------------------------------
void Sprite::Scale(float factor) {
  sprite.setScale(factor, factor);
}

// ------------------------------------------------------------------
// SetAnimationSpeed
// ------------------------------------------------------------------
void Sprite::SetAnimationSpeed(unsigned int time) {
  if (current_animation) {
    current_animation->SetSpeed(time);
  }
}

} // GameLib
