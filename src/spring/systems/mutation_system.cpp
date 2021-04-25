//
// Created by kernel on 25.04.2021.
//

#include <lib/ecs/entity_manager.h>
#include <spring/components/characteristics_component.h>
#include <spring/configuration.h>
#include <spring/state.h>
#include <spring/systems/mutation_system.h>

#include <random>
#include <set>

MutationSystem::MutationSystem(EntityManager* entity_manager, SystemManager* system_manager, const State& state,
                               const Configuration& config)
    : ISystem(entity_manager, system_manager),
      state_(const_cast<State&>(state)),
      config_(const_cast<Configuration&>(config)) {
  gen_ = std::mt19937(rd_());
}

void MutationSystem::OnUpdate() {
  if (state_.GetGenerationNumber() > n_) {
    std::uniform_real_distribution<double> distA(0.0, 1);
    std::uniform_real_distribution<double> distB(0, 48);
    std::uniform_real_distribution<double> distC(config_.GetMinD(), config_.GetMaxD());
    std::uniform_real_distribution<double> indexRand(0, state_.GetDescendants().size() - 1);

    size_t count = state_.GetDescendants().size() * config_.GetPm();

    std::set<int> indexes;

    while (indexes.size() < count) {
      indexes.insert(static_cast<int>(indexRand(gen_)));
    }

    for (int index : indexes) {
      if (distA(gen_) > 0.5) {
        auto entity = GetEntityManager().CreateEntity()->Add<CharacteristicsComponent>(
            state_.GetRangeD()[static_cast<int>(distB(gen_))],
            state_.GetDescendants()[index]->Get<CharacteristicsComponent>()->D_, config_.GetF2(), config_.GetG(),
            config_.GetH());

        state_.AddDescendant(entity);

        GetEntityManager().DeleteEntity(state_.GetDescendants()[index]->GetId());
        state_.ReplaceDescendant(index, entity);
      } else {
        auto entity = GetEntityManager().CreateEntity()->Add<CharacteristicsComponent>(
            state_.GetDescendants()[index]->Get<CharacteristicsComponent>()->d_,
            (distC(gen_) + state_.GetDescendants()[index]->Get<CharacteristicsComponent>()->D_) / 2, config_.GetF2(),
            config_.GetG(), config_.GetH());

        state_.AddDescendant(entity);

        GetEntityManager().DeleteEntity(state_.GetDescendants()[index]->GetId());
        state_.ReplaceDescendant(index, entity);
      }
    }
    n_++;
  }
}
