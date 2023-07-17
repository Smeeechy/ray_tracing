//
// Created by Daryn Smith on 7/13/23.
//

#ifndef RAY_TRACING_UTIL_H
#define RAY_TRACING_UTIL_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>

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

inline double random_double() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

inline double random_double(const double min, const double max) {
  return min + (max - min) * random_double(); // returns a random number [min, max)
}

inline double clamp(const double value, const double min, const double max) {
  if (value < min) return min;
  if (value > max) return max;
  return value;
}

// common headers
#include "ray.h"
#include "vec3.h"

#endif //RAY_TRACING_UTIL_H
