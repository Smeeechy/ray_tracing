#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

double rng() {
  return static_cast<double>(rand()) / (RAND_MAX);
}

bool hit_sphere(const point3 sphere_origin, const double sphere_radius, const ray r) {
  const vec3 oc = r.origin() - sphere_origin;
  const double a = dot(r.direction(), r.direction());
  const double b = 2 * dot(oc, r.direction());
  const double c = dot(oc, oc) - (sphere_radius * sphere_radius);
  const double discriminant = (b * b) - (4 * a * c);
  return discriminant > 0;
}

color ray_color(const ray r) {
  if (hit_sphere(point3(0, 0, -1), 0.5, r)) return {rng(), rng(), rng()};
  
  // map y value of unit vector of given ray's direction between 0 and 1
  vec3 unit_direction = unit_vector(r.direction());
  double t = 0.5 * (unit_direction.y() + 1);
  
  color gradient_start(1, 1, 1);    // white
  color gradient_end(0.5, 0.7, 1);  // sky blue
  
  // simple linear interpolation
  return ((1 - t) * gradient_start) + (t * gradient_end);
}

int main() {
  
  // image
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 1000;
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
