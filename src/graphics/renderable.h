#pragma once

#include "../math/shapes.h"
#include "color.h"
#include <SFML/Graphics.hpp>

//#define RENDER_DEBUG

namespace GameLib {

class Sprite;

struct TextureTracker {

    TextureTracker()
     : tex(nullptr)
     , ref_counter(1) {
    }

    explicit TextureTracker(sf::Texture *t)
     : tex(t)
     , ref_counter(1) {
    }

    sf::Texture *tex;
    unsigned int ref_counter;
};

class Window;
class Renderable {
  public:
    /**
     * @brief def constructor
     */
    Renderable();

    /**
     * @brief constructor
     * @param filename image file name
     */
    explicit Renderable(const std::string &filename);

    /**
     * @brief copy constructor
     */
    Renderable(const Renderable &other);

    /**
     * @brief destructor
     */
    virtual ~Renderable();

    /**
      * @brief gets the Drawable aspect
      */
    inline virtual const sf::Drawable &get() {
        return sprite;
    }

    /**
     * \breif set the deat rect
     * @param x dest x
     * @param y dest y
     */
    virtual inline void SetPosition(float x, float y) {
        geometry.x = x;
        geometry.y = y;
        sprite.setPosition(sf::Vector2f(x, y));
    }

    /**
     * \breif get the dest rect
     */
    inline Point GetPosition() {
        return Point(geometry.x, geometry.y);
    }

    /**
     * @brief render
     * @param window render target
     */
    virtual void Render(Window &window);

    /**
     * \breif move it
     * @param dx delta x
     * @param dy delta y
     */
    virtual inline void Move(float dx, float dy) {
        geometry.x += dx;
        geometry.y += dy;
    }

    /**
     * @brief get current dimensions
     */
    virtual inline float GetWidth() {
        return geometry.w;
    }

    /**
     * @brief get current dimensions
     */
    virtual inline float GetHeight() {
        return geometry.h;
    }

    /**
     * @brief get original texture size
     */
    inline unsigned int GetTextureWidth() {
        if (texture != nullptr) {
            return texture->getSize().x;
        }
        return 0;
    }

    /**
     * @brief get original texture size
     */
    inline unsigned int GetTextureHeight() {
        if (texture != nullptr) {
            return texture->getSize().y;
        }
        return 0;
    }

    /**
     * @brief color swap
     */
    void SwapColors(std::vector<std::pair<sf::Color, sf::Color>> palette);

    /// depth
    int z_order;

    /// a renderable entity may or may not have a shadow
    Sprite *shadow;

    /// the floor z for shdows
    static int shadow_z;

    /// visible
    bool visible = true;

  protected:
    /// geometry
    Rectangle geometry;

    /// sfml texture
    sf::Texture *texture;

    /// a paletted texture
    sf::Texture *paletted_texture;

    /// a sfml sprite
    sf::Sprite sprite;

    /// save as reference to texture being used
    std::string texture_filename;

    /**
     * @brief helper to count number of renderables made
     */
    static unsigned int count_renderables();

    /**
     * @brief helper set the texture
     */
    void set_texture(const std::string &filename);
};

} // GameLib
