//
// Created by kernel on 26.04.2021.
//

#include <spring/configuration.h>
#include <spring/stage.h>
#include <spring/state.h>
#include <spring/systems/formation_system.h>

#include <cstdio>

FormationSystem::FormationSystem(EntityManager* entity_manager, SystemManager* system_manager, const State& state,
                                 const Configuration& config)
    : ISystem(entity_manager, system_manager),
      state_(const_cast<State&>(state)),
      config_(const_cast<Configuration&>(config)) {}

void FormationSystem::OnUpdate() {
  if (state_.stage == FORMATION) {
    state_.ExtractSurvivors(config_.GetPc());

    for (const auto& entity : state_.GetActors()) {
      GetEntityManager().DeleteEntity(entity->GetId());
    }
    state_.ClearActors();
    state_.AddSurvivors();
    state_.AddDescendants();

    state_.ClearSurvivors();
    state_.ClearDescendants();

    state_.ShuffleActors();

    state_.IncGeneration();
    state_.stage = ANALYSIS;

    printf("avg fitness: %.2f\n", state_.GetAverageFitness());
  }
}
void FormationSystem::OnPostUpdate() {}
