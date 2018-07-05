#include "perspective.h"
#include "../graphics/sprite.h"
#include "../math/constants.h"
namespace GameLib {

/// dictated by the graphics style
const float Y_OFFSET_DUE_TO_HEIGHT = 0.1333;
const float CM_PER_PIXEL = 7.6f;

void Perspective::Perspetcivize(GameEntity &entity, float camera_height) {
  // size depending on distance from camera
  float z_position = entity.physical.position.z;
  float dist_from_camera = camera_height - entity.physical.position.z;
  float angular_diameter =
      2 * (atanf(entity.physical.dimensions.w / (2 * dist_from_camera)));
  float degs = DEGREES(angular_diameter);
  float sprite_scale_factor = degs / entity.physical.dimensions.w;
  Sprite &sprite = static_cast<Sprite &>(entity.renderable);
  float sprite_ratio = entity.physical.dimensions.w / sprite.sprite_width;
  sprite_scale_factor *= sprite_ratio;
  sprite.Scale(sprite_scale_factor);

  // y offset due to height
  float z_cm = entity.physical.position.z * CM_PER_PIXEL;

  if (z_cm) {
    // tmp hard code offset = 0.133px per cm
    float y_offset = Y_OFFSET_DUE_TO_HEIGHT * z_cm;
    entity.renderable.Move(0, -y_offset);
  }

  // update the shadow
  Sprite* shadow = sprite.shadow;
  if(shadow){
      shadow->Scale(sprite_scale_factor);
  }
}
}  // namespace GameLib
