//
// Created by kernel on 25.04.2021.
//

#include <lib/ecs/entity_manager.h>
#include <spring/components/characteristics_component.h>
#include <spring/configuration.h>
#include <spring/state.h>
#include <spring/systems/crossover_system.h>

#include <unordered_set>

CrossoverSystem::CrossoverSystem(EntityManager* entity_manager, SystemManager* system_manager, const State& state,
                                   const Configuration& config)
    : ISystem(entity_manager, system_manager),
      state_(const_cast<State&>(state)),
      config_(const_cast<Configuration&>(config)) {
  gen_ = std::mt19937(rd_());
}

void CrossoverSystem::OnUpdate() {
  if (state_.stage == CROSSOVER) {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::uniform_real_distribution<double> indexRand(0, state_.GetActors().size() - 1);

    for (int i = 0; i < 2; i++) {
      std::unordered_set<int> indexes;

      while (indexes.size() < (state_.GetActors().size() - state_.GetSurvivors().size())) {
        indexes.insert(static_cast<int>(indexRand(gen_)));
      }

      bool isParentInSearch = false;
      int freeParent = -1;

      for (int index : indexes) {
        if (!isParentInSearch) {
          freeParent = index;
          isParentInSearch = true;
        } else {
          if (dist(gen_) > 0.5) {
            auto currentIndex = state_.GetActors()[index]->Get<CharacteristicsComponent>()->d_index_;

            auto entity = GetEntityManager().CreateEntity()->
                          Add<CharacteristicsComponent>(
                currentIndex,
                state_.GetActors()[index]->Get<CharacteristicsComponent>()->d_,
                state_.GetActors()[freeParent]->Get<CharacteristicsComponent>()->D_,
                config_.GetF2(),
                config_.GetG(),
                config_.GetH3())->
                          Add<FitnessComponent>(-1);

            state_.AddDescendant(entity);
          } else {
            auto currentIndex = state_.GetActors()[freeParent]->Get<CharacteristicsComponent>()->d_index_;

            auto entity = GetEntityManager().CreateEntity()->
                          Add<CharacteristicsComponent>(
                currentIndex,
                state_.GetActors()[freeParent]->Get<CharacteristicsComponent>()->d_,
                state_.GetActors()[index]->Get<CharacteristicsComponent>()->D_,
                config_.GetF2(),
                config_.GetG(),
                config_.GetH3())->
                          Add<FitnessComponent>(-1);

            state_.AddDescendant(entity);
          }
          isParentInSearch = false;
        }
      }
    }
    state_.stage = MUTATION;
  }
}
