#pragma once

#include "../game/game_entity.h"
#include "../math/shapes.h"
#include <SFML/Graphics.hpp>

namespace GameLib {

class Camera : public GameEntity {
public:
    Camera() : GameEntity (new Physical(), new Renderable()) {
        following = nullptr;
        name = "camera";
        zoom_steps = 0;
        zooming = 0;
    }
    ~Camera() {
        delete physical;
        delete renderable;
    }

    /**
     * @brief the main update function for an entity
     * @param dt time delta
     */
    virtual void Update (float dt) override;

    /**
     * @brief set up the game world rect
     * @param world_rect rectangle
     */
    inline void SetWorldRect (const Rectangle &world_rect) {
        world = world_rect;
    }

    /**
     * @brief follow a game entity
     * @param e game entity to follow
     */
    void Follow (GameEntity *e);

    /**
     * @brief get the current viewport
     */
    inline Rectangle GetViewport() {
        return Rectangle (view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2, view.getSize().x, view.getSize().y);
    }

    /**
     * @brief zoom the camera
     */
    void ZoomOut() {
        zooming = 1;
    }

    /**
     * @brief zoom the camera
     */
    void ZoomIn() {
        zooming = -1;
    }

    // TODO
    sf::View view;

    float abs_zoom = 0;

protected:
    /// whole game world
    Rectangle world;

    /// only move camera if target outside this Rectangle
    Rectangle anchor_rect;

    /// track which entity we are following
    GameEntity *following;

    /// track zooming
    int zoom_steps;
    int zooming;

    /**
     * @brief helper to update position
     */
    void update_position();

    /**
     * @brief zoom
     */
    void zoom();
};

} // GameLib
