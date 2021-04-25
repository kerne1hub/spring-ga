//
// Created by kernel on 25.04.2021.
//

#include <lib/ecs/entity_manager.h>
#include <spring/components/characteristics_component.h>
#include <spring/components/fitness_component.h>
#include <spring/configuration.h>
#include <spring/state.h>
#include <spring/systems/analysis_system.h>

AnalysisSystem::AnalysisSystem(EntityManager* entity_manager, SystemManager* system_manager, const State& state,
                               const Configuration& config)
    : ISystem(entity_manager, system_manager),
      state_(const_cast<State&>(state)),
      config_(const_cast<Configuration&>(config)) {}

void AnalysisSystem::OnUpdate() {
  if (state_.GetGenerationNumber() > generation_) {
    auto actors = state_.GetActors();
    auto size = actors.size();
    size_t id = -1;
    double best = 10e8;
    double avg = 0;

    for (auto actor : actors) {
      actor->Add<FitnessComponent>(-1);
      double fitness = DetermineFitness(actor);

      avg += fitness;

      if (fitness < best) {
        best = fitness;
        id = actor->GetId();
      }
    }

    avg /= size;

    state_.SetAverageFitness(avg);
    state_.SetSolutionId(id);
    generation_++;
  }
}

double AnalysisSystem::DetermineFitness(Entity* actor) {
  auto fc = actor->Get<FitnessComponent>();

  double penalty = 1;
  double fitness = DetermineFunction(actor) + penalty * DetermineRestrictions(actor);
  fc->value_ = fitness;

  return fitness;
}

double AnalysisSystem::DetermineFunction(Entity* actor) {
  auto chars = actor->Get<CharacteristicsComponent>();
  return ((3.14159 * chars->d_ * chars->d_) / 4) * (chars->D_ - chars->d_) * (chars->n_ + 2);
}

double AnalysisSystem::DetermineRestrictions(Entity* actor) {
  auto chars = actor->Get<CharacteristicsComponent>();
  auto fitness = actor->Get<FitnessComponent>();

  double fi1 = DetermineFi1Diapason(chars->t3_);
  double fi2 = DetermineFi2Diapason(chars->d_, chars->n_);
  double fi4 = DetermineFi4Diapason(chars->n_);

  fitness->fi1_ = fi1;
  fitness->fi2_ = fi2;
  fitness->fi4_ = fi4;

  return pow(((fi1 + std::abs(fi1)) / 2), 2) +
         pow(((fi2 + std::abs(fi2)) / 2), 2) +
         pow(((fi4 + std::abs(fi4)) / 2), 2);
}

double AnalysisSystem::DetermineFi1Diapason(double t3) {
  return t3 - config_.GetTKr();
}

double AnalysisSystem::DetermineFi2Diapason(double d, double n) {
  return config_.GetH() * 1000 + d * (n + 2) - config_.GetH() * 1000;
}

double AnalysisSystem::DetermineFi4Diapason(double n) {
  return 3 - n;
}
