#include "util.h"
#include "color.h"
#include "entity_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

#include <iostream>

color ray_color(const ray& incident, const entity& world, const int depth) {
  if (depth <= 0) return {0, 0, 0};
  
  hit_record record;
  if (world.hit(incident, 0.001, infinity, record)) { // 0.001 corrects for shadow acne
    ray scattered;
    color attenuation;
    if (record.material_ptr->scatter(incident, record, attenuation, scattered)) return attenuation * ray_color(scattered, world, depth - 1);
    return {0, 0, 0};
  }
  
  // ray didn't hit anything, show the background gradient
  const vec3 unit_direction = unit_vector(incident.direction());
  double t = 0.5 * (unit_direction.y() + 1.0);
  color gradient_start = from_hex(0xDDFFDF);  // white-ish
  color gradient_end = from_hex(0x15AAFF);    // sky blue
  return ((1.0 - t) * gradient_start) + (t * gradient_end);
}

int main() {
  
  // image
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 640;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 100;
  const int max_depth = 50;
  
  // world
  entity_list world;
  const shared_ptr<material> material_ground = make_shared<lambertian>(from_hex(0x111111));
  const shared_ptr<material> material_center = make_shared<lambertian>(from_hex(0xA8A196));
  const shared_ptr<material> material_left = make_shared<metal>(from_hex(0x7D7463), .05);
  const shared_ptr<material> material_right = make_shared<metal>(from_hex(0xFE0000), .33);
  world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
  world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
  
  // camera
  const camera cam;
  
  // render
  std::cout << "P3" << std::endl << image_width << ' ' << image_height << std::endl << "255" << std::endl;
  for (int row = image_height - 1; row >= 0; row--) {
    std::cerr << "\rProgress: " << image_height - row << '/' << image_height << std::flush;
    for (int col = 0; col < image_width; col++) {
      color pixel_color(0, 0, 0);
      for (int sample = 0; sample < samples_per_pixel; sample++) {
        const double u = (col + random_double()) / (image_width - 1);
        const double v = (row + random_double()) / (image_height - 1);
        ray ray_ = cam.get_ray(u, v);
        pixel_color += ray_color(ray_, world, max_depth);
      }
      write_color(std::cout, pixel_color, samples_per_pixel);
    }
  }
  
  std::cerr << std::endl << "Finished." << std::endl;
  return 0;
}
