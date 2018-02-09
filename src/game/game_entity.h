#pragma once

#include <set>

#include "../graphics/renderable.h"
#include "../physics/physical.h"

namespace GameLib {

/** @brief possible anchor point types */
enum AnchorType {
    ANCHOR_NONE,
    ANCHOR_CENTER,  /// entity centeres around center of sprite
    ANCHOR_BASELINE /// entity centers around center-bottom of sprite
};

class GameEntity {
  public:
    /**
    * @brief construct with ready made physical aspect
    * @param p ready made physical aspect - subclass responsible for memory!
    * @param r ready made renderable aspect- subclass responsible for memory!
    */
    explicit GameEntity(Physical *p, Renderable *r);

    /**
     * @brief destruct
     */
    virtual ~GameEntity(void);

    /**
     * @brief the main update function for an entity
     * @param dt time delta
     */
    virtual void Update(float dt);

    /**
     * @brief manually move the entity
     * @param dx x delta
     * @param dy y delta
     */
    void Move(float dx, float dy);

    /**
     * @brief set position
     * @param x x pos
     * @param y y pos
     * @param z z pos
     */
    void SetPosition(float x, float y, float z = 0);

    Point GetPosition();

    /**
     * @brief set a uniqueentity id
     */
    void SetName(const std::string &name);

    /**
     * @brief get a uniqueentity id
     */
    std::string GetName();

    /**
     * @brief like a rpc call
     * @param params list of params
     */
    virtual void Call(std::vector<std::string> params);

    /// physical aspect associated with this entity
    Physical *physical;

    /// renderable aspect associated with this entity
    Renderable *renderable;

    /// easy access without dereferencing each time
    Vector3 &velocity;

    /// center point
    AnchorType anchor_type;

    /// overlay (hud)
    bool hud = false;

  protected:
    /**
     * @brief align the sprite accordig to physical position, sprite size and
     * anchor type
     */
    void anchor();

    /// unique name
    std::string name;

    /// keep the list unique
    static std::set<std::string> entity_names;

  public:
    friend class Game;
};
} // GameLib
