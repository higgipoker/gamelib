#pragma once

#include "../physics/physical.h"
#include "../graphics/renderable.h"

namespace GameLib {

/** \brief possible anchor point types */
enum anchor_point {
	ANCHOR_NONE,
	ANCHOR_CENTER,		/// entity centeres around center of sprite
	ANCHOR_BASELINE		/// entity centers around center-bottom of sprite
};

class GameEntity {
public:
    /**
    * \brief construct
    */
    GameEntity(void);

    /**
     * \brief destruct
     */
    virtual ~GameEntity(void);

    /**
     * \brief the main update function for an entity
     * \param dt time delta
     */
    virtual void Update(float dt);

    /**
     * \brief manually move the entity
	 * \param dx x delta
	 * \param dy y delta
     */
    void Move(float dx, float dy);

	/**
	 * \brief set position
	 * \param x x pos
	 * \param y y pos
	 * \param z z pos
	 */
    void SetPosition(float x, float y, float z = 0);

    /// a game entity has a physical and graphical aspect
    Physical 	*physical;
    Renderable 	*renderable;

	/// center point
	anchor_point anchor_type;

	/// overlay (hud)
	bool hud = false;

	/// unique name
	std::string name;

protected:

	/**
	 * \brief align the sprite accordig to physical position, sprite size and anchor type
	 */
	void anchor();

};
}// GameLib
