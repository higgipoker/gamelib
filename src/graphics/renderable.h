#pragma once

#include "../math/shapes.h"
#include "color.h"
#include <SFML/Graphics.hpp>
#include <iostream>

//#define RENDER_DEBUG

namespace GameLib {

/**
 * @brief ref counter for textures
 */
struct TrackableTexture {

    /**
     * @brief constructor
     */
    TrackableTexture() : tex(nullptr), ref_counter(1) {}

    /**
     * @brief constructor with initialiser
     */
    explicit TrackableTexture(sf::Texture *t) : tex(t), ref_counter(1) {}

    /// the actual texture
    sf::Texture *tex;

    /// reference counter
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
    inline virtual const sf::Drawable &get() { return sprite; }

    /**
     * @brief set the deat rect
     * @param x dest x
     * @param y dest y
     */
    virtual void SetPosition(float x, float y);

    /**
     * @brief get the dest rect
     */
    inline Point GetPosition() { return Point(geometry.x, geometry.y); }

    /**
     * @brief render
     * @param window render target
     */
    virtual void Render(Window &window);

    /**
     * @brief move it
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
    virtual inline float GetWidth() { return geometry.w; }

    /**
     * @brief get current dimensions
     */
    virtual inline float GetHeight() { return geometry.h; }

    /**
     * @brief color swap
     */
    void SwapColors(std::vector<std::pair<Color, Color>> palette);

    /// depth
    int z_order;

    /// the floor z for shdows
    static int shadow_z;

    /// visible
    bool visible = true;

  protected:
    /// geometry
    Rectangle geometry;

    /// sfml texture
    sf::Texture *texture;

    /// since textures can be shared, when we swap colors (paletted texture), we
    /// have to save it in a new texture and not
    /// overwrite the original
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
