//
// Created by kernel on 26.04.2021.
//

#ifndef INCLUDE_SPRING_SYSTEMS_FORMATION_SYSTEM_H_
#define INCLUDE_SPRING_SYSTEMS_FORMATION_SYSTEM_H_

#include <lib/ecs/entity.h>
#include <lib/ecs/entity_manager.h>
#include <lib/ecs/system.h>

class FormationSystem : public ISystem {
 private:
  State& state_;
  Configuration& config_;

 public:
  FormationSystem(EntityManager* entity_manager, SystemManager* system_manager, const State& state,
                  const Configuration& config);

 protected:
  void OnUpdate() override;
  void OnPostUpdate() override;
};

#endif  // INCLUDE_SPRING_SYSTEMS_FORMATION_SYSTEM_H_
