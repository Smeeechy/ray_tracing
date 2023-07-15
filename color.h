//
// Created by Daryn Smith on 7/8/23.
//

#ifndef RAY_TRACING_COLOR_H
#define RAY_TRACING_COLOR_H

#include "vec3.h"
#include <iostream>

void write_color(std::ostream &out, const color color_, const int sample_count) {
  double r = color_.x();
  double g = color_.y();
  double b = color_.z();
  
  const double scale = 1.0 / sample_count;
  r *= scale;
  g *= scale;
  b *= scale;
  
  out << static_cast<int>(256 * clamp(r, 0.0, .999)) << ' ' <<
         static_cast<int>(256 * clamp(g, 0.0, .999)) << ' ' <<
         static_cast<int>(256 * clamp(b, 0.0, .999)) << std::endl;
}

#endif //RAY_TRACING_COLOR_H
