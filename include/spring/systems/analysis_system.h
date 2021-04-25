//
// Created by kernel on 25.04.2021.
//

#ifndef INCLUDE_SPRING_SYSTEMS_ANALYSIS_SYSTEM_H_
#define INCLUDE_SPRING_SYSTEMS_ANALYSIS_SYSTEM_H_

#include <lib/ecs/system.h>
#include <spring/state.h>

class AnalysisSystem : public ISystem {
 private:
  State& state_;
  Configuration& config_;
  int generation_ = 0;

 public:
  AnalysisSystem(EntityManager* entity_manager, SystemManager* system_manager, const State& state,
  const Configuration& config);

 protected:
  void OnUpdate() override;
  double DetermineFi1Diapason(double t3);
  double DetermineFi2Diapason(double d, double n);
  double DetermineFi4Diapason(double n);
  double DetermineFitness(Entity* actor);
  double DetermineFunction(Entity* actor);
  double DetermineRestrictions(Entity* actor);
};

#endif  // INCLUDE_SPRING_SYSTEMS_ANALYSIS_SYSTEM_H_
