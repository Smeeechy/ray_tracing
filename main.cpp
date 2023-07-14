#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

color ray_color(const ray r) {
  // return color based off normal vector of hit sphere
  double t = hit_sphere(point3(0, 0, -1), 0.5, r);
  if (t > 0) {
    const vec3 normal = unit_vector(r.at(t) - point3(0, 0, -1));
    return 0.5 * color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
  }
  
  // ray didn't hit anything, show the background gradient
  const vec3 unit_direction = unit_vector(r.direction());
  t = 0.5 * (unit_direction.y() + 1);
  color gradient_start(1, 1, 1);    // white
  color gradient_end(0.5, 0.7, 1);  // sky blue
  return ((1 - t) * gradient_start) + (t * gradient_end);
}

int main() {
  
  // image
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 256;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  
  // camera
  const double viewport_height = 2.0;
  const double viewport_width = aspect_ratio * viewport_height;
  const double focal_length = 1.0;
  const point3 origin(0, 0, 0);
  const vec3 horizontal(viewport_width, 0, 0);
  const vec3 vertical(0, viewport_height, 0);
  const point3 lower_left_corner = origin - (horizontal / 2) - (vertical / 2) - vec3(0, 0, focal_length);
  
  // render
  std::cout << "P3" << std::endl << image_width << ' ' << image_height << std::endl << "255" << std::endl;
  for (int row = image_height - 1; row >= 0; row--) {
    std::cerr << "\rProgress: " << image_height - row << '/' << image_height << std::flush;
    for (int col = 0; col < image_width; col++) {
      const double u = static_cast<double>(col) / (image_width - 1);
      const double v = static_cast<double>(row) / (image_height - 1);
      const vec3 direction = lower_left_corner + (u * horizontal) + (v * vertical) - origin;
      const ray r(origin, direction);
      color pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }
  
  std::cerr << std::endl << "Finished." << std::endl;
  return 0;
}
