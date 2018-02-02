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
  double x;
  double y;
  double z;

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
  inline Vector3(double xi, double yi, double zi) {
    x = xi;
    y = yi;
    z = zi;
  }

  // ----------------------------------------------------
  //  constructor (with initialisers)
  // ----------------------------------------------------
  inline Vector3(double xi, double yi) {
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
  double operator[](int idx) const {
    double ret = 0;
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
  inline Vector3 &operator*=(const double rhs) {
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;

    return *this;
  }

  // ----------------------------------------------------
  //   /= operator (scalar)
  // ----------------------------------------------------
  inline Vector3 &operator/=(const double rhs) {
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
  inline const Vector3 operator*(const double rhs) const {
    return Vector3(*this) *= rhs;
  }

  // ----------------------------------------------------
  //   / operator (scalar)
  // ----------------------------------------------------
  inline const Vector3 operator/(const double rhs) const {
    return Vector3(*this) /= rhs;
  }

  // ----------------------------------------------------
  //   cross product operator
  // ----------------------------------------------------
  inline const Vector3 operator^(Vector3 &v) {
    return Vector3(this->y * v.z - this->z * v.y, -this->x * v.z + this->z * v.x, this->x * v.y - this->y * v.x);
  }

  // ----------------------------------------------------
  //   dot product operator
  // ----------------------------------------------------
  inline double operator*(Vector3 &rhs) {
    return (this->x * rhs.x + this->y * rhs.y + this->z * rhs.z);
  }

  // ----------------------------------------------------
  // multiply by method call
  // ----------------------------------------------------
  inline void multiply(double _scalar) {
    this->x *= _scalar;
    this->y *= _scalar;
    this->z *= _scalar;
  }

  // ----------------------------------------------------
  //  normalised
  // ----------------------------------------------------
  inline Vector3 normalised(void) {
    Vector3 normalized(this->x, this->y, this->z);

    double m = sqrt(x * x + y * y + z * z);

    if (m <= TOL) {
      m = 1;
    }

    normalized.x /= m;
    normalized.y /= m;
    normalized.z /= m;

    if (fabs(normalized.x) < TOL) {
      normalized.x = 0;
    }
    if (fabs(normalized.y) < TOL) {
      normalized.y = 0;
    }
    if (fabs(normalized.z) < TOL) {
      normalized.z = 0;
    }

    return normalized;
  }

  // ----------------------------------------------------
  //  normalise
  // ----------------------------------------------------
  inline void normalise() {
    // use the already existing get normalised function
    Vector3 tmp = this->normalised();
    x = tmp.x;
    y = tmp.y;
    z = tmp.z;
  }

  // ----------------------------------------------------
  //  reflect
  // ----------------------------------------------------
  inline Vector3 Reflect(Vector3 &normal) const {
    double dot = (this->x * normal.x) + this->y * normal.y;
    dot *= 2;
    Vector3 reflected = normal * dot - *this;
    return reflected.Reverse();
  }

  // ----------------------------------------------------
  //  project
  // ----------------------------------------------------
  inline double projectionOn(Vector3 line) {
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
  inline Vector3 rotated(double a, double x_origin = 0, double y_origin = 0) const {
    a = RADIANS(a);

    Vector3 rotated = *this;

    rotated.x -= x_origin;
    rotated.y -= y_origin;

    double nx = cos(a) * rotated.x - sin(a) * rotated.y;
    double ny = sin(a) * rotated.x + cos(a) * rotated.y;

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
    if (fabs(this->x - v.x) < TOL && fabs(this->y - v.y) < TOL && fabs(this->z - v.z) < TOL) {
      return true;
    }
    return false;
  }

  // ----------------------------------------------------
  //   test for equality
  // ----------------------------------------------------
  inline bool equals(const Vector3 &v, double tolerancce) {
    if (fabs(this->x - v.x) < tolerancce && fabs(this->y - v.y) < tolerancce && fabs(this->z - v.z) < tolerancce) {
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
    double nearest_radians = RADIANS(nearest_angle);

    // get the angle of this vector
    double angle = atan2(this->y, this->x);

    // remainder between 2 angles
    double remainder = std::fmod(angle, nearest_radians);

    // if there is a remainder, do the rounding
    if (remainder > TOL) {
      double new_angle = round(angle / nearest_radians) * nearest_radians;

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
  inline double perpProduct(const Vector3 &v, bool right_normal = true) {
    double componentY, componentX;

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
  inline void polar(double mag, double radians) {
    this->x = mag * cos(radians);
    this->y = mag * sin(radians);
  }

  // ----------------------------------------------------
  //   setMagnitude
  // ----------------------------------------------------
  inline void setMagnitude(double mag) {
    double ang_current = this->angle();
    this->polar(mag, ang_current);
  }

  // ----------------------------------------------------
  // get magnitude of this vector
  // ----------------------------------------------------
  inline double magnitude(void) const {
    return sqrt(x * x + y * y + z * z);
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
  inline double magSquared(void) {
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
  inline double dotProduct(const Vector3 &v) const {
    return (this->x * v.x + this->y * v.y + this->z * v.z);
  }

  // ----------------------------------------------------
  //   get angle in degrees
  // ----------------------------------------------------
  inline double angle(void) {
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
  inline static bool isMovingTowards(Vector3 testPoint, Vector3 objectPosition, Vector3 objectVelocity) {
    Vector3 toPoint = testPoint - objectPosition; // a vector going from your obect to the point
    double dot = toPoint.dotProduct(objectVelocity);
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
