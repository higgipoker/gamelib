/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
/**
 * @file vector3.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once

#include "constants.h"
#include "shapes.h"
#include <cmath>
#include <math.h>

namespace GameLib {

//  -----------------------------------------------------------
//
//  A class to represent a Vector
//
//  convention is to return a new vector for operation and not
//    mutate *this. Except for operator overloads, naturally
//
//  -----------------------------------------------------------

class Vector3 {
  public:
    // ----------------------------------------------------
    // components
    // ----------------------------------------------------
    float x;
    float y;
    float z;

    // ----------------------------------------------------
    //  constructor
    // ----------------------------------------------------
    inline Vector3(void) {
        x = 0;
        y = 0;
        z = 0;
    }

    // ----------------------------------------------------
    //  constructor (with initialisers)
    // ----------------------------------------------------
    inline Vector3(float xi, float yi, float zi) {
        x = xi;
        y = yi;
        z = zi;
    }

    // ----------------------------------------------------
    //  constructor (with initialisers)
    // ----------------------------------------------------
    inline Vector3(float xi, float yi) {
        x = xi;
        y = yi;
        z = 0;
    }

    // ----------------------------------------------------
    //  constructor (with initialisers)
    // ----------------------------------------------------
    explicit inline Vector3(const Point &_p) {
        x = _p.x;
        y = _p.y;
        z = 0;
    }

    // ----------------------------------------------------
    // [] operator
    // ----------------------------------------------------
    float operator[](int idx) const {
        float ret = 0;
        switch (idx) {
            case 0:
                ret = x;
                break;
            case 1:
                ret = y;
                break;
            case 2:
                ret = z;
                break;
            default:
                ret = 0;
                break;
        }
        return ret;
    }

    // ----------------------------------------------------
    //   += operator
    // ----------------------------------------------------
    inline Vector3 &operator+=(const Vector3 &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;

        return *this;
    }

    // ----------------------------------------------------
    //   -= operator
    // ----------------------------------------------------
    inline Vector3 &operator-=(const Vector3 &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;

        return *this;
    }

    // ----------------------------------------------------
    //   *= operator
    // ----------------------------------------------------
    inline Vector3 &operator*=(const Vector3 &rhs) {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;

        return *this;
    }

    // ----------------------------------------------------
    //   *= operator (sccalar)
    // ----------------------------------------------------
    inline Vector3 &operator*=(const float rhs) {
        x *= rhs;
        y *= rhs;
        z *= rhs;

        return *this;
    }

    // ----------------------------------------------------
    //   /= operator (scalar)
    // ----------------------------------------------------
    inline Vector3 &operator/=(const float rhs) {
        x /= rhs;
        y /= rhs;
        z /= rhs;

        return *this;
    }

    // ----------------------------------------------------
    //   + operator
    // ----------------------------------------------------
    inline const Vector3 operator+(const Vector3 &rhs) const {
        return Vector3(*this) += rhs;
    }

    // ----------------------------------------------------
    //   - operator
    // ----------------------------------------------------
    inline const Vector3 operator-(const Vector3 &rhs) const {
        return Vector3(*this) -= rhs;
    }

    // ----------------------------------------------------
    //   * operator (scalar)
    // ----------------------------------------------------
    inline const Vector3 operator*(const float rhs) const {
        return Vector3(*this) *= rhs;
    }

    // ----------------------------------------------------
    //   / operator (scalar)
    // ----------------------------------------------------
    inline const Vector3 operator/(const float rhs) const {
        return Vector3(*this) /= rhs;
    }

    // ----------------------------------------------------
    //   cross product operator
    // ----------------------------------------------------
    inline const Vector3 operator^(Vector3 &v) {
        return Vector3(y * v.z - z * v.y, -x * v.z + z * v.x, x * v.y - y * v.x);
    }

    // ----------------------------------------------------
    //   dot product operator
    // ----------------------------------------------------
    inline float operator*(Vector3 &rhs) {
        return (x * rhs.x + y * rhs.y + z * rhs.z);
    }

    // ----------------------------------------------------
    // multiply by method call
    // ----------------------------------------------------
    inline void multiply(float _scalar) {
        x *= _scalar;
        y *= _scalar;
        z *= _scalar;
    }

    // ----------------------------------------------------
    //  normalised
    // ----------------------------------------------------
    inline Vector3 normalised(void) {
        Vector3 normalized(x, y, z);

        float m = sqrtf(x * x + y * y + z * z);

        if (m <= TOL) {
            m = 1;
        }

        normalized.x /= m;
        normalized.y /= m;
        normalized.z /= m;

        if (fabsf(normalized.x) < TOL) {
            normalized.x = 0;
        }
        if (fabsf(normalized.y) < TOL) {
            normalized.y = 0;
        }
        if (fabsf(normalized.z) < TOL) {
            normalized.z = 0;
        }

        return normalized;
    }

    // ----------------------------------------------------
    //  normalise
    // ----------------------------------------------------
    inline void normalise() {
        // use the already existing get normalised function
        Vector3 tmp = normalised();
        x = tmp.x;
        y = tmp.y;
        z = tmp.z;
    }

    // ----------------------------------------------------
    //  reflect
    // ----------------------------------------------------
    inline Vector3 Reflect(Vector3 &normal) const {
        float dot = (x * normal.x) + y * normal.y;
        dot *= 2;
        Vector3 reflected = normal * dot - *this;
        return reflected.Reverse();
    }

    // ----------------------------------------------------
    //  project
    // ----------------------------------------------------
    inline float projectionOn(Vector3 line) {
        line = line.normalised();
        return dotProduct(line);
    }

    // ----------------------------------------------------
    //  get perpendicular (normal vector)
    // ----------------------------------------------------
    inline Vector3 getPerpendicular() {
        Vector3 perp(y, -x);
        return perp;
    }

    // ----------------------------------------------------
    //  rotated
    // ----------------------------------------------------
    inline Vector3 rotated(float a, float x_origin = 0, float y_origin = 0) const {
        a = RADIANS(a);

        Vector3 rotated = *this;

        rotated.x -= x_origin;
        rotated.y -= y_origin;

        float nx = cosf(a) * rotated.x - sinf(a) * rotated.y;
        float ny = sinf(a) * rotated.x + cosf(a) * rotated.y;

        rotated.x = nx;
        rotated.y = ny;

        rotated.x += x_origin;
        rotated.y += y_origin;

        return rotated;
    }

    // ----------------------------------------------------
    //   test for equality
    // ----------------------------------------------------
    inline bool equals(const Vector3 &v) {
        if (fabsf(x - v.x) < TOL && fabsf(y - v.y) < TOL && fabsf(z - v.z) < TOL) {
            return true;
        }
        return false;
    }

    // ----------------------------------------------------
    //   test for equality
    // ----------------------------------------------------
    inline bool equals(const Vector3 &v, float tolerancce) {
        if (fabsf(x - v.x) < tolerancce && fabsf(y - v.y) < tolerancce && fabsf(z - v.z) < tolerancce) {
            return true;
        }
        return false;
    }

    // ----------------------------------------------------
    //   round the angle to nearest x degrees
    // ----------------------------------------------------
    inline Vector3 roundAngle(int nearest_angle) {
        // vector to return
        Vector3 rounded;

        // convert to radians
        float nearest_radians = RADIANS(nearest_angle);

        // get the angle of this vector
        float angle = atan2f(y, x);

        // remainder between 2 angles
        float remainder = std::fmod(angle, nearest_radians);

        // if there is a remainder, do the rounding
        if (remainder > TOL) {
            float new_angle = roundf(angle / nearest_radians) * nearest_radians;

            rounded.x = cosf(new_angle);
            rounded.y = sinf(new_angle);
        } else {
            rounded.x = x;
            rounded.y = y;
            rounded.z = z;
        }

        if (fabsf(rounded.x) < TOL) {
            rounded.x = 0;
        }
        if (fabsf(rounded.y) < TOL) {
            rounded.y = 0;
        }
        if (fabsf(rounded.z) < TOL) {
            rounded.z = 0;
        }

        return rounded.normalised();
    }

    // ----------------------------------------------------
    //   perpProduct
    // ----------------------------------------------------
    inline float perpProduct(const Vector3 &v, bool right_normal = true) {
        float componentY, componentX;

        if (right_normal) {
            componentX = y * v.x;
            componentY = -1 * x * v.y;
        } else {
            componentX = -1 * y * v.x;
            componentY = x * v.y;
        }
        return componentX + componentY;
    }

    // ----------------------------------------------------
    //   polar
    // ----------------------------------------------------
    inline void polar(float mag, float radians) {
        x = mag * cosf(radians);
        y = mag * sinf(radians);
    }

    // ----------------------------------------------------
    //   setMagnitude
    // ----------------------------------------------------
    inline void setMagnitude(float mag) {
        float ang_current = angle();
        polar(mag, ang_current);
    }

    // ----------------------------------------------------
    // get magnitude of this vector
    // ----------------------------------------------------
    inline float magnitude(void) const {
        return sqrtf(x * x + y * y + z * z);
    }

    // ----------------------------------------------------
    // get magnitude of this vector in 2d
    // ----------------------------------------------------
    inline float magnidude2d(void) {
        return sqrtf(x * x + y * y);
    }

    // ----------------------------------------------------
    // get unit vector
    // ----------------------------------------------------
    static inline Vector3 getUnitVector(Vector3 v) {
        return v / v.magnitude();
    }

    // ----------------------------------------------------
    // get mag squared
    // ----------------------------------------------------
    inline float magSquared(void) {
        return magnitude() * magnitude();
    }

    // ----------------------------------------------------
    // get reversed
    // ----------------------------------------------------
    inline Vector3 Reverse(void) {
        Vector3 reversed(-x, -y, -z);
        return reversed;
    }

    // ----------------------------------------------------
    //   dot product
    // ----------------------------------------------------
    inline float dotProduct(const Vector3 &v) const {
        return (x * v.x + y * v.y + z * v.z);
    }

    // ----------------------------------------------------
    //   get angle in degrees
    // ----------------------------------------------------
    inline float angle(void) {
        return DEGREES(atan2f(y, x));
    }

    // ----------------------------------------------------
    //   reset components to zero
    // ----------------------------------------------------
    inline void reset() {
        x = y = z = 0;
    }

    // ----------------------------------------------------
    //   normalizes all components to 1's or 0's
    // ----------------------------------------------------
    inline void normalizeToUnits() {
        if (x > 0) {
            x = 1;
        } else if (x < 0) {
            x = -1;
        }

        if (y > 0) {
            y = 1;
        } else if (y < 0) {
            y = -1;
        }
    }

    // ----------------------------------------------------
    // get normalised to units
    // ----------------------------------------------------
    inline Vector3 getNormalizedToUnits(void) {
        Vector3 to_return(x, y, z);
        to_return.normalizeToUnits();
        return to_return;
    }

    // ----------------------------------------------------
    // find if a vector is moving towards a point
    // ----------------------------------------------------
    inline static bool isMovingTowards(Vector3 testPoint, Vector3 objectPosition, Vector3 objectVelocity) {
        Vector3 toPoint = testPoint - objectPosition;
        float dot = toPoint.dotProduct(objectVelocity);
        return dot > 0;
    }

    // ----------------------------------------------------
    //  get a point
    // ----------------------------------------------------
    inline Point ToPoint() {
        return Point(x, y);
    }
};

} // namespace GameLib
