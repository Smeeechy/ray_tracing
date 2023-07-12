//
// Created by Daryn Smith on 7/8/23.
//

#ifndef RAY_TRACING_RAY_H
#define RAY_TRACING_RAY_H

#include "vec3.h"

class ray {
  private:
  point3 origin_;
  vec3 direction_;
  
  public:
  // constructors
  ray() = default;
  ray(const point3& origin, const vec3& direction) : origin_(origin), direction_(direction) {}
  
  // getters
  [[nodiscard]] point3 origin() const { return origin_; }
  [[nodiscard]] vec3 direction() const { return direction_; }
  
  // used to find position along ray
  [[nodiscard]] point3 at(double t) const { return origin_ + direction_ * t; }
  
};


#endif //RAY_TRACING_RAY_H
