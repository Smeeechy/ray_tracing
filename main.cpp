#include "color.h"
#include "vec3.h"

#include <iostream>

int main() {
  // image
  const int image_width = 256;
  const int image_height = 256;
  
  // render
  std::cout << "P3" << std::endl << image_width << ' ' << image_height << std::endl << "255" << std::endl;
  for (int row = image_height - 1; row >= 0; row--) {
    int row_count = image_height - row;
    std::cerr << "\rProgress: " << row_count << '/' << image_height;
    for (int pixel = 0; pixel < image_width; pixel++) {
      color pixel_color(double(pixel) / (image_width - 1), double(row) / (image_height - 1), 0.25);
      write_color(std::cout, pixel_color);
    }
  }
  
  std::cerr << std::endl << "Finished." << std::endl;
  return 0;
}
