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
  explicit entity_list(const shared_ptr<entity>& entity) { add(entity); }
  
  void clear() { entities.clear(); }
  void add(const shared_ptr<entity>& entity) { entities.push_back(entity); }
  
  bool hit(ray incident, double t_min, double t_max, hit_record& record) const override;
};

bool entity_list::hit(ray incident, double t_min, double t_max, hit_record& record) const {
  hit_record temp_record;
  bool hit_anything = false;
  double closest = t_max;
  
  for (const shared_ptr<entity>& entity : entities) {
    if (entity->hit(incident, t_min, closest, temp_record)) {
      hit_anything = true;
      closest = temp_record.t;
      record = temp_record;
    }
  }
  
  return hit_anything;
}

#endif //RAY_TRACING_ENTITY_LIST_H
