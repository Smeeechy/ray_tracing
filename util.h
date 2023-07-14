//
// Created by Daryn Smith on 7/13/23.
//

#ifndef RAY_TRACING_UTIL_H
#define RAY_TRACING_UTIL_H

#include <cmath>
#include <limits>
#include <memory>

// usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// functions
inline double radians(const double degrees) {
  return degrees * pi / 180.0;
}

// common headers
#include "ray.h"
#include "vec3.h"

#endif //RAY_TRACING_UTIL_H
