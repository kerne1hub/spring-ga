//
// Created by kernel on 25.04.2021.
//

#ifndef INCLUDE_SPRING_SYSTEMS_CROSSOVER_SYSTEM_H_
#define INCLUDE_SPRING_SYSTEMS_CROSSOVER_SYSTEM_H_

#include <lib/ecs/entity.h>
#include <lib/ecs/system.h>

#include <random>

class CrossoverSystem : public ISystem {
 private:
  std::random_device rd_;
  std::mt19937 gen_;

  State& state_;
  Configuration& config_;

 public:
  CrossoverSystem(EntityManager* entity_manager, SystemManager* system_manager, const State& state,
  const Configuration& config);

 protected:
  void OnUpdate() override;
};

#endif  // INCLUDE_SPRING_SYSTEMS_CROSSOVER_SYSTEM_H_
