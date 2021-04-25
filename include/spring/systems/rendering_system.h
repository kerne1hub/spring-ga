//
// Created by kernel on 25.04.2021.
//

#ifndef INCLUDE_SPRING_SYSTEMS_RENDERING_SYSTEM_H_
#define INCLUDE_SPRING_SYSTEMS_RENDERING_SYSTEM_H_

#include <lib/ecs/entity.h>
#include <lib/ecs/system.h>
#include <lib/ui/page.h>
#include <spring/state.h>

#include <vector>

class RenderingSystem : public ISystem {
  State& state_;
  std::vector<Page>* pages_;

 public:
  RenderingSystem(EntityManager* entity_manager, SystemManager* system_manager, const State& state,
                  std::vector<Page>* pages);

 protected:
  void OnUpdate() override;
};

#endif  // INCLUDE_SPRING_SYSTEMS_RENDERING_SYSTEM_H_
