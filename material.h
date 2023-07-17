//
// Created by Daryn Smith on 7/15/23.
//

#ifndef RAY_TRACING_MATERIAL_H
#define RAY_TRACING_MATERIAL_H

#include "util.h"

struct hit_record;

class material {
  public:
  virtual bool scatter(const ray &incident, const hit_record &record, color &attenuation, ray &scattered) const = 0;
};

class lambertian : public material {
  private:
  const color albedo;
  
  public:
  explicit lambertian(const color color_) : albedo(color_) {}
  
  bool scatter(const ray &incident, const hit_record &record, color &attenuation, ray &scattered) const override {
    vec3 scatter_direction = record.normal + random_unit_vector();
    if (scatter_direction.near_zero()) scatter_direction = record.normal;
    scattered = ray(record.point, scatter_direction);
    attenuation = albedo;
    return true;
  }
};

class metal : public material {
  private:
  const color albedo;
  
  public:
  explicit metal(const color color_) : albedo(color_) {}
  
  bool scatter(const ray &incident, const hit_record &record, color &attenuation, ray &scattered) const override {
    const vec3 reflected = reflect(unit_vector(incident.direction()), record.normal);
    scattered = ray(record.point, reflected);
    attenuation = albedo;
    return dot(reflected, record.normal) > 0;
  }
};

#endif //RAY_TRACING_MATERIAL_H
