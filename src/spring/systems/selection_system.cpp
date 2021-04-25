//
// Created by kernel on 25.04.2021.
//

#include <lib/ecs/entity_manager.h>
#include <spring/configuration.h>
#include <spring/state.h>
#include <spring/systems/selection_system.h>

SelectionSystem::SelectionSystem(EntityManager* entity_manager, SystemManager* system_manager, const State& state,
                                 const Configuration& config)
    : ISystem(entity_manager, system_manager),
      state_(const_cast<State&>(state)),
      config_(const_cast<Configuration&>(config)) {}

void SelectionSystem::OnUpdate() {
  if (state_.GetGenerationNumber() > n_) {
    state_.SortActors();
    state_.SelectSurvivors(config_.GetPc());
    n_++;
  }
}
