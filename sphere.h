//
// Created by Daryn Smith on 7/13/23.
//

#ifndef RAY_TRACING_SPHERE_H
#define RAY_TRACING_SPHERE_H

#include "entity.h"
#include "vec3.h"

class sphere : public entity {
  public:
  const point3 center;
  const double radius;
  
  sphere(point3 center_, double radius_) : center(center_), radius(radius_) {};
  [[nodiscard]] bool hit(ray r, double t_min, double t_max, hit_record &record) const override;
};

bool sphere::hit(const ray r, const double t_min, const double t_max, hit_record &record) const {
  const vec3 oc = r.origin() - center;
  const double a = r.direction().length_squared();
  const double half_b = dot(oc, r.direction());
  const double c = oc.length_squared() - (radius * radius);
  
  // no hit
  const double discriminant = (half_b * half_b) - (a * c);
  if (discriminant < 0) return false;
  
  // find the nearest root within bounds of t_min and t_max
  const double discriminant_root = sqrt(discriminant);
  double root = (-half_b - discriminant_root) / a;
  if (root < t_min || root > t_max) {
    root = (-half_b + discriminant_root) / a;
    if (root < t_min || root > t_max) return false;
  }
  
  // save hit data
  record.t = root;
  record.point = r.at(root);
  const vec3 outward_normal = (r.at(root) - center) / radius;
  record.set_face_normal(r, outward_normal);
  
  return true;
}


#endif //RAY_TRACING_SPHERE_H
