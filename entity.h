//
// Created by Daryn Smith on 7/13/23.
//

#ifndef RAY_TRACING_ENTITY_H
#define RAY_TRACING_ENTITY_H

#include "ray.h"

struct hit_record {
  point3 point;
  vec3 normal;
  double t = 0;
  bool front_face = true;
  
  // determine if we're hitting the entity from the outside (front) or the inside (back)
  inline void set_face_normal(const ray r, const vec3 outward_normal) {
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class entity {
  public:
  [[nodiscard]] virtual bool hit(ray r, double t_min, double t_max, hit_record &record) const = 0;
};

#endif //RAY_TRACING_ENTITY_H
