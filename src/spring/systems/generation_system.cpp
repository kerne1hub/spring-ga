//
// Created by kernel on 25.04.2021.
//
#include <lib/ecs/entity_manager.h>
#include <spring/components/characteristics_component.h>
#include <spring/configuration.h>
#include <spring/state.h>
#include <spring/systems/generation_system.h>

GenerationSystem::GenerationSystem(EntityManager* entity_manager, SystemManager* system_manager, const State& state,
                                   const Configuration& config, int n)
    : ISystem(entity_manager, system_manager),
      state_(const_cast<State&>(state)),
      config_(const_cast<Configuration&>(config)),
      n_(n) {
  gen_ = std::mt19937(rd_());
}

void GenerationSystem::OnUpdate() {
  if (state_.stage == GENERATION) {
    auto minD = config_.GetMinD();
    auto maxD = config_.GetMaxD();
    std::uniform_real_distribution<double> distA(minD, maxD);
    std::uniform_real_distribution<double> distB(0.0, 48.0);

    while (static_cast<int>(state_.GetActors().size()) < n_) {
      int index = static_cast<int>(distB(gen_));
      auto entity = GetEntityManager().CreateEntity()
                        ->Add<CharacteristicsComponent>(index, state_.GetRangeD()[index], distA(gen_), config_.GetF2(),
                                                        config_.GetG(), config_.GetH3())
                        ->Add<FitnessComponent>(-1);
      state_.AddActor(entity);
    }

    state_.stage = ANALYSIS;
  }
}
