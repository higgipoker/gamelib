#pragma once
#include "renderable.h"

#include <map>

#include "animation.h"
#include "color.h"
#include <SFML/Graphics.hpp>

namespace GameLib {

class Sprite : public Renderable {
  public:
    /**
     * @brief constructor
     * @param filename spritesheet filename
     * @param num_rows number of sprite rows in the filen
     * @param num_cols number of sprite columns in the file
     */
    Sprite(const std::string &filename, unsigned int num_rows, unsigned int num_cols);

    /**
      * @brief destruct
      */
    ~Sprite();

    /**
     * @brief render
     * @param window render target
     */
    virtual void Render(Window &window) override;

    /**
     * @brief set the current frame in the spriteset
     * @param frame which frame
     */
    void SetFrame(unsigned int frame);

    /**
     * @brief add an animation with init list
     * @param animname name
     * @param frametime timing
     * @param loopanim loopanim
     * @param framelist frames
     */
    void AddAnimation(const std::string &animname, float frametime, bool loopanim, std::vector<unsigned int> framelist);

    /**
     * @brief add an already constructed animation
     * @param anim anim to add
     */
    void AddAnimation(Animation anim);

    /**
     * @brief update animation
     */
    virtual void Animate();

    /**
     * @brief move it
     * @param dx x delta
     * @param dy y delta
     */
    void Move(float dx, float dy) override;

    /**
     * @brief set the active animation
     * @param name name
     */
    void SetAnimation(const std::string &name);

    /**
     * @brief scaling
     * @param x_factor x scale factor
     * @param y_factor y scale factor
     */
    void Scale(float x_factor, float y_factor);

    /**
     * @brief scaling (with equal factors in x and y)
     * @param factor scale factor
     */
    void Scale(float factor);

    /**
     * @brief get current width
     */
    virtual inline float GetWidth() override {
        return sprite_width;
    }

    /**
     * @brief get current height
     */
    virtual inline float GetHeight() override {
        return sprite_height;
    }

    /**
     * @brief dynamically alter the speed of the current animation
     * @param speed new speed
     */
    void SetAnimationSpeed(unsigned int speed);

    /**
     * @brief set origin for transformations
     * @param x x origin
     * @param y y origin
     */
    inline void SetOrigin(float x, float y) {
        sprite.setOrigin(x, y);
    }

    /// a renderable entity may or may not have a shadow
    Sprite *shadow;

  protected:
    /// spritesheet rects
    std::vector<sf::IntRect> rects;

    /// each sprite width and height
    unsigned int sprite_width, sprite_height;

    /// a list of possible animations for the sprite (list of frame numbers to cycle through)
    std::vector<Animation> animations;

    /// pointer to current animation
    Animation *current_animation;
};

} // GameLib
