#pragma once
namespace GameLib {
// ----------------------------------------------------
//  tolerance value for normalizing and comparisons
// ----------------------------------------------------
static const float TOL = 0.001f;

// ----------------------------------------------------
//  define pi
// ----------------------------------------------------
static const float PI = 3.14159265359f;

// ----------------------------------------------------
//  convert degrees to radians
// ----------------------------------------------------
#define RADIANS(a) a *(PI / 180.0f)

// ----------------------------------------------------
//  convert radians to degrees
// ----------------------------------------------------
#define DEGREES(a) a *(180.0f / PI)

// ----------------------------------------------------
//  is_zero
// ----------------------------------------------------
static inline bool is_zero (float n) {
    if (n < 0 - TOL || n > TOL) {
        return false;
    }
    return true;
}

} // GameLib
