#pragma once

#include "../math/shapes.h"
#include "../math/vector3.h"

namespace GameLib {

/**
 * @brief base physical
 */
class Physical {
public:
    /**
     * @brief construct
     */
    Physical (void);

    /**
     * @brief destruct
     */
    virtual ~Physical (void);

    /// position
    Vector3 position;

    /// velocity
    Vector3 velocity;

    /// accelleration
    Vector3 acceleration;

    /// dimensions
    Rectangle dimensions;

    /**
     * @brief convenience (have public access to position too)
     * @param _new_position new pos to set
     */
    inline void SetPosition (const Vector3 &_new_position) {
        position.x = _new_position.x;
        position.y = _new_position.y;
        position.z = _new_position.z;
    }

    /**
     * @brief convenience
     */
    inline void ResetPosition (void) {
        position.x = position.y = position.z = 0;
    }

    /**
     * @brief convenience (have public access to velocity too)
     * @param _new_velocity new pos to set
     */
    inline void SetVelocity (const Vector3 &_new_velocity) {
        velocity.x = _new_velocity.x;
        velocity.y = _new_velocity.y;
        velocity.z = _new_velocity.z;
    }

    /**
     * @brief convenience
     */
    inline void ResetVelocity (void) {
        velocity.x = velocity.y = velocity.z = 0;
    }

    /**
     * @brief convenience (have public access to acceleration too)
     * @param _new_acceleration new pos to set
     */
    inline void SetAcceleration (const Vector3 &_new_acceleration) {
        acceleration.x = _new_acceleration.x;
        acceleration.y = _new_acceleration.y;
        acceleration.z = _new_acceleration.z;
    }

    /**
     * @brief convenience
     */
    inline void ResetAcceleration (void) {
        acceleration.x = acceleration.y = acceleration.z = 0;
    }

    /**
     * @brief convenience
     * @param _new_dimensions new dimensions to set
     */
    inline void SetDimensions (const Rectangle &_new_dimensions) {
        dimensions.x = _new_dimensions.x;
        dimensions.y = _new_dimensions.y;
        dimensions.w = _new_dimensions.w;
        dimensions.h = _new_dimensions.h;
    }

    /**
     * @brief convenience
     * @param _width w
     * @param _height h
     */
    inline void SetDimensions (int _width, int _height) {
        dimensions.w = _width;
        dimensions.h = _height;
    }

    /**
     * @brief get an angle depending on the x, y velocity components
     */
    inline unsigned int GetAngle() const {

        if (velocity.x < 0 && velocity.y < 0)
            return 45;

        else if (is_zero (velocity.x) && velocity.y < 0)
            return 90;

        else if (velocity.x > TOL && velocity.y < 0)
            return 135;

        else if (velocity.x > TOL && is_zero (velocity.y))
            return 180;

        else if (velocity.x > TOL && velocity.y > 0)
            return 225;

        else if (is_zero (velocity.x) && velocity.y > 0)
            return 270;

        else if (velocity.x < TOL && velocity.y > 0)
            return 315;

        return 0;
    }
};

} // GameLib
