#pragma once

#include <math.h>
#include <cmath>
#include "constants.h"
#include "shapes.h"

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
        switch (idx) {
        case 0:
            return x;
            break;
        case 1:
            return y;
            break;
        case 2:
            return z;
            break;
        default:
            return 0;
            break;
        }
        return 0;
    }

    // ----------------------------------------------------
    //   = operator
    // ----------------------------------------------------
    inline Vector3 &operator=(const Vector3 &rhs) {
        // Only do assignment if RHS is a different object from this.
        if (this != &rhs) {
            this->x = rhs.x;
            this->y = rhs.y;
            this->z = rhs.z;
        }

        return *this;
    }

    // ----------------------------------------------------
    //   += operator
    // ----------------------------------------------------
    inline Vector3 &operator+=(const Vector3 &rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;

        return *this;
    }

    // ----------------------------------------------------
    //   -= operator
    // ----------------------------------------------------
    inline Vector3 &operator-=(const Vector3 &rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;
        this->z -= rhs.z;

        return *this;
    }

    // ----------------------------------------------------
    //   *= operator
    // ----------------------------------------------------
    inline Vector3 &operator*=(const Vector3 &rhs) {
        this->x *= rhs.x;
        this->y *= rhs.y;
        this->z *= rhs.z;

        return *this;
    }

    // ----------------------------------------------------
    //   *= operator (sccalar)
    // ----------------------------------------------------
    inline Vector3 &operator*=(const float rhs) {
        this->x *= rhs;
        this->y *= rhs;
        this->z *= rhs;

        return *this;
    }

    // ----------------------------------------------------
    //   /= operator (scalar)
    // ----------------------------------------------------
    inline Vector3 &operator/=(const float rhs) {
        this->x /= rhs;
        this->y /= rhs;
        this->z /= rhs;

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
        return Vector3(this->y * v.z - this->z * v.y,
                       -this->x * v.z + this->z * v.x,
                       this->x * v.y - this->y * v.x);
    }

    // ----------------------------------------------------
    //   dot product operator
    // ----------------------------------------------------
    inline float operator*(Vector3 &rhs) {
        return (this->x * rhs.x + this->y * rhs.y + this->z * rhs.z);
    }

    // ----------------------------------------------------
    //   comparison operator
    // ----------------------------------------------------
    inline bool operator==(Vector3 &rhs) const {
        return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z);
    }

    // ----------------------------------------------------
    // multiply by method call
    // ----------------------------------------------------
    inline void multiply(float _scalar) {
        this->x *= _scalar;
        this->y *= _scalar;
        this->z *= _scalar;
    }

    // ----------------------------------------------------
    //  normalised
    // ----------------------------------------------------
    inline Vector3 normalised(void) {
        Vector3 normalized(this->x, this->y, this->z);

        float m = (float)sqrt(x * x + y * y + z * z);

        if (m <= TOL) {
            m = 1;
        }

        normalized.x /= m;
        normalized.y /= m;
        normalized.z /= m;

        if (fabs(normalized.x) < TOL) {
            normalized.x = 0.0f;
        }
        if (fabs(normalized.y) < TOL) {
            normalized.y = 0.0f;
        }
        if (fabs(normalized.z) < TOL) {
            normalized.z = 0.0f;
        }

        return normalized;
    }

    // ----------------------------------------------------
    //  normalise
    // ----------------------------------------------------
    inline void normalise() {
        float m = (float)sqrt(x * x + y * y + z * z);

        if (m <= TOL) {
            m = 1;
        }

        this->x /= m;
        this->y /= m;
        this->z /= m;

        if (fabs(this->x) < TOL) {
            this->x = 0.0f;
        }
        if (fabs(this->y) < TOL) {
            this->y = 0.0f;
        }
        if (fabs(this->z) < TOL) {
            this->z = 0.0f;
        }
    }

    // ----------------------------------------------------
    //  reflect
    // ----------------------------------------------------
    inline Vector3 Reflect(Vector3 &normal) const {
        float dot = (this->x * normal.x) + this->y * normal.y;
        dot *= 2;
        Vector3 reflected = normal * dot - *this;
        return reflected.Reverse();
    }

    // ----------------------------------------------------
    //  project
    // ----------------------------------------------------
    inline float projectionOn(Vector3 line) {
        line = line.normalised();
        return this->dotProduct(line);
    }

    // ----------------------------------------------------
    //  get perpendicular (normal vector)
    // ----------------------------------------------------
    inline Vector3 getPerpendicular() {
        Vector3 perp(this->y, -this->x);
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

        float nx = cos(a) * rotated.x - sin(a) * rotated.y;
        float ny = sin(a) * rotated.x + cos(a) * rotated.y;

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
        if (fabs(this->x - v.x) < TOL && fabs(this->y - v.y) < TOL &&
                fabs(this->z - v.z) < TOL) {
            return true;
        }
        return false;
    }

    // ----------------------------------------------------
    //   test for equality
    // ----------------------------------------------------
    inline bool equals(const Vector3 &v, float tolerancce) {
        if (fabs(this->x - v.x) < tolerancce && fabs(this->y - v.y) < tolerancce &&
                fabs(this->z - v.z) < tolerancce) {
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
        float angle = atan2(this->y, this->x);

        // remainder between 2 angles
        float remainder = std::fmod(angle, nearest_radians);

        // if there is a remainder, do the rounding
        if (remainder != 0) {
            float new_angle = round(angle / nearest_radians) * nearest_radians;

            rounded.x = cos(new_angle);
            rounded.y = sin(new_angle);
        } else {
            rounded.x = this->x;
            rounded.y = this->y;
            rounded.z = this->z;
        }

        if (fabs(rounded.x) < TOL) {
            rounded.x = 0;
        }
        if (fabs(rounded.y) < TOL) {
            rounded.y = 0;
        }
        if (fabs(rounded.z) < TOL) {
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
            componentX = this->y * v.x;
            componentY = -1 * this->x * v.y;
        } else {
            componentX = -1 * this->y * v.x;
            componentY = this->x * v.y;
        }
        return componentX + componentY;
    }

    // ----------------------------------------------------
    //   polar
    // ----------------------------------------------------
    inline void polar(float mag, float radians) {
        this->x = mag * cos(radians);
        this->y = mag * sin(radians);
    }

    // ----------------------------------------------------
    //   setMagnitude
    // ----------------------------------------------------
    inline void setMagnitude(float mag) {
        float ang_current = this->angle();
        this->polar(mag, ang_current);
    }

    // ----------------------------------------------------
    // get magnitude of this vector
    // ----------------------------------------------------
    inline float magnitude(void) const {
        return (float)sqrt(x * x + y * y + z * z);
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
        return this->magnitude() * this->magnitude();
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
        return (this->x * v.x + this->y * v.y + this->z * v.z);
    }

    // ----------------------------------------------------
    //   get angle in degrees
    // ----------------------------------------------------
    inline float angle(void) {
        return DEGREES(atan2(y, x));
    }

    // ----------------------------------------------------
    //   reset components to zero
    // ----------------------------------------------------
    inline void reset() {
        this->x = this->y = this->z = 0;
    }

    // ----------------------------------------------------
    //   normalizes all components to 1's or 0's
    // ----------------------------------------------------
    inline void normalizeToUnits() {
        if (this->x > 0) {
            this->x = 1;
        } else if (this->x < 0) {
            this->x = -1;
        }

        if (this->y > 0) {
            this->y = 1;
        } else if (this->y < 0) {
            this->y = -1;
        }
    }

    // ----------------------------------------------------
    // get normalised to units
    // ----------------------------------------------------
    inline Vector3 getNormalizedToUnits(void) {
        Vector3 to_return(this->x, this->y, this->z);
        to_return.normalizeToUnits();
        return to_return;
    }

    // ----------------------------------------------------
    // find if a vector is moving towards a point
    // ----------------------------------------------------
    inline static bool isMovingTowards(Vector3 testPoint, Vector3 objectPosition,
                                       Vector3 objectVelocity) {
        Vector3 toPoint =
            testPoint -
            objectPosition;  // a vector going from your obect to the point
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

}  // namespace GameLib
