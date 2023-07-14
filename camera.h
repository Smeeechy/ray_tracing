//
// Created by Daryn Smith on 7/14/23.
//

#ifndef RAY_TRACING_CAMERA_H
#define RAY_TRACING_CAMERA_H

#include "util.h"

class camera {
  
  private:
  point3 origin;
  point3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
  
  public:
  camera() {
    const double aspect_ratio = 16.0 / 9.0;
    const double viewport_height = 2.0;
    const double viewport_width = aspect_ratio * viewport_height;
    const double focal_length = 1.0;
    origin = point3(0, 0, 0);
    horizontal = vec3(viewport_width, 0, 0);
    vertical = vec3(0, viewport_height, 0);
    lower_left_corner = origin - (horizontal / 2) - (vertical / 2) - vec3(0, 0, focal_length);
  }
  
  [[nodiscard]] ray get_ray(double u, double v) const {
    const vec3 direction = lower_left_corner + (u * horizontal) + (v * vertical) - origin;
    return {origin, direction};
  }
  
};

#endif //RAY_TRACING_CAMERA_H
