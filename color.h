//
// Created by Daryn Smith on 7/8/23.
//

#ifndef RAY_TRACING_COLOR_H
#define RAY_TRACING_COLOR_H

#include "vec3.h"
#include <iostream>

void write_color(std::ostream& out, const color color, const int sample_count) {
  double r = color.x();
  double g = color.y();
  double b = color.z();
  
  // gamma correction where gamma = 2: n ^ 1/2 == sqrt(n)
  const double scale = 1.0 / sample_count;
  r = sqrt(r * scale);
  g = sqrt(g * scale);
  b = sqrt(b * scale);
  
  out << static_cast<int>(256 * clamp(r, 0.0, .999)) << ' ' <<
         static_cast<int>(256 * clamp(g, 0.0, .999)) << ' ' <<
         static_cast<int>(256 * clamp(b, 0.0, .999)) << std::endl;
}

color from_hex(const int hex) {
  return {double((hex >> 16) & 255) / 256.0, double((hex >> 8) & 255) / 256.0, double(hex & 255) / 256.0};
}

#endif //RAY_TRACING_COLOR_H
