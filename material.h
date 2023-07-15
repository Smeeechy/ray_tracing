//
// Created by Daryn Smith on 7/15/23.
//

#ifndef RAY_TRACING_MATERIAL_H
#define RAY_TRACING_MATERIAL_H

#include "util.h"

struct hit_record;

class material {
  public:
  virtual bool scatter(ray ray_in, hit_record &record, color attenuation, ray scattered) const = 0;
};

#endif //RAY_TRACING_MATERIAL_H
