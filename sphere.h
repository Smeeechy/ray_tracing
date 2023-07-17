//
// Created by Daryn Smith on 7/13/23.
//

#ifndef RAY_TRACING_SPHERE_H
#define RAY_TRACING_SPHERE_H

#include <utility>

#include "entity.h"
#include "vec3.h"

class sphere : public entity {
  public:
  const point3 center;
  const double radius;
  const shared_ptr<material> material_ptr;
  
  sphere(point3 center, double radius, shared_ptr<material> material_ptr) :
    center(center), radius(radius), material_ptr(std::move(material_ptr)) {};
  
  [[nodiscard]] bool hit(ray incident, double t_min, double t_max, hit_record& record) const override;
};

bool sphere::hit(const ray incident, const double t_min, const double t_max, hit_record& record) const {
  const vec3 oc = incident.origin() - center;
  const double a = incident.direction().length_squared();
  const double half_b = dot(oc, incident.direction());
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
  record.point_of_contact = incident.at(root);
  const vec3 outward_normal = (incident.at(root) - center) / radius;
  record.set_face_normal(incident, outward_normal);
  record.material_ptr = material_ptr;
  
  return true;
}


#endif //RAY_TRACING_SPHERE_H
