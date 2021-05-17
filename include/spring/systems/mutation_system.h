//
// Created by kernel on 25.04.2021.
//

#ifndef INCLUDE_SPRING_SYSTEMS_MUTATION_SYSTEM_H_
#define INCLUDE_SPRING_SYSTEMS_MUTATION_SYSTEM_H_

#include <lib/ecs/entity.h>
#include <lib/ecs/system.h>
#include <spring/configuration.h>
#include <spring/state.h>

#include <random>

class MutationSystem : public ISystem {
 private:
  std::random_device rd_;
  std::mt19937 gen_;

  State& state_;
  Configuration& config_;
  int n_ = 0;

 public:
  MutationSystem(EntityManager* entity_manager, SystemManager* system_manager, const State& state,
                 const Configuration& config);

 protected:
  void OnUpdate() override;

  int SoftMutate(int min, int max, int current);
};

#endif  // INCLUDE_SPRING_SYSTEMS_MUTATION_SYSTEM_H_
