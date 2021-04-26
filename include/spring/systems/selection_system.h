//
// Created by kernel on 25.04.2021.
//

#ifndef INCLUDE_SPRING_SYSTEMS_SELECTION_SYSTEM_H_
#define INCLUDE_SPRING_SYSTEMS_SELECTION_SYSTEM_H_

#include <lib/ecs/entity.h>
#include <lib/ecs/system.h>

class SelectionSystem : public ISystem {
 private:
  State& state_;
  Configuration& config_;

 public:
  SelectionSystem(EntityManager* entity_manager, SystemManager* system_manager, const State& state,
  const Configuration& config);

 protected:
  void OnUpdate() override;
};

#endif  // INCLUDE_SPRING_SYSTEMS_SELECTION_SYSTEM_H_
