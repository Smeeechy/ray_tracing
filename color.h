//
// Created by Daryn Smith on 7/8/23.
//

#ifndef RAY_TRACING_COLOR_H
#define RAY_TRACING_COLOR_H

#include "vec3.h"
#include <iostream>

inline int map_component(const double color_component) { return static_cast<int>(255.999 * color_component); }

void write_color(std::ostream &out, color color) {
  out << map_component(color.x()) << ' ' << map_component(color.y()) << ' ' << map_component(color.z()) << std::endl;
}

#endif //RAY_TRACING_COLOR_H
