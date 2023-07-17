//
// Created by Daryn Smith on 7/15/23.
//

#ifndef RAY_TRACING_MATERIAL_H
#define RAY_TRACING_MATERIAL_H

#include "util.h"

struct hit_record;

class material {
  public:
  virtual bool scatter(const ray& incident, const hit_record& record, color& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
  private:
  const color albedo;
  
  public:
  explicit lambertian(const color color) : albedo(color) {}
  
  bool scatter(const ray& incident, const hit_record& record, color& attenuation, ray& scattered) const override {
    vec3 scatter_direction = record.normal + random_unit_vector();
    if (scatter_direction.near_zero()) scatter_direction = record.normal;
    scattered = ray(record.point_of_contact, scatter_direction);
    attenuation = albedo;
    return true;
  }
};

class metal : public material {
  private:
  const color albedo;
  const double fuzz;
  
  public:
  explicit metal(const color color, const double fuzz) : albedo(color), fuzz(fuzz < 1 ? fuzz : 1) {}
  
  bool scatter(const ray& incident, const hit_record& record, color& attenuation, ray& scattered) const override {
    const vec3 reflected = reflect(unit_vector(incident.direction()), record.normal);
    scattered = ray(record.point_of_contact, reflected + fuzz * random_in_unit_sphere());
    attenuation = albedo;
    return dot(reflected, record.normal) > 0;
  }
};

#endif //RAY_TRACING_MATERIAL_H
