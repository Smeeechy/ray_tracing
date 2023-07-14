//
// Created by Daryn Smith on 7/13/23.
//

#ifndef RAY_TRACING_ENTITY_LIST_H
#define RAY_TRACING_ENTITY_LIST_H

#include "entity.h"

#include <utility>
#include <vector>
#include <memory>
using std::vector;
using std::shared_ptr;

class entity_list : public entity {
  private:
  vector<shared_ptr<entity>> entities;
  
  public:
  entity_list() = default;
  explicit entity_list(const shared_ptr<entity> &entity_) { add(entity_); }
  
  void clear() { entities.clear(); }
  void add(const shared_ptr<entity> &entity_) { entities.push_back(entity_); }
  
  bool hit(ray r, double t_min, double t_max, hit_record &record) const override;
};

bool entity_list::hit(ray r, double t_min, double t_max, hit_record &record) const {
  hit_record temp_record;
  bool hit_anything = false;
  double closest = t_max;
  
  for (const shared_ptr<entity> &entity_ : entities) {
    if (entity_->hit(r, t_min, closest, temp_record)) {
      hit_anything = true;
      closest = temp_record.t;
      record = temp_record;
    }
  }
  
  return hit_anything;
}

#endif //RAY_TRACING_ENTITY_LIST_H
