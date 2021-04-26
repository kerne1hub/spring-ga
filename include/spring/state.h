//
// Created by kernel on 24.04.2021.
//

#ifndef INCLUDE_SPRING_STATE_H_
#define INCLUDE_SPRING_STATE_H_

#include <lib/ecs/entity.h>
#include <spring/components/fitness_component.h>
#include <spring/stage.h>

#include <algorithm>
#include <random>
#include <vector>

class State {
  std::vector<Entity*> actors_;
  std::vector<Entity*> survivors_;
  std::vector<Entity*> descendants_;
  int generation_ = 0;
  int generationLimit_{};
  size_t solutionId_ = -1;
  double averageFitness_ = -1;

  std::random_device rd_;

 private:
  double range_d[48] = {0.16, 0.18, 0.2,  0.22, 0.25, 0.28, 0.3,  0.32,  // ГОСТ-3282-74, мм
                        0.35, 0.36, 0.37, 0.4,  0.45, 0.5,  0.55, 0.56, 0.6, 0.63, 0.7, 0.8, 0.85, 0.9,
                        0.95, 1,    1.1,  1.2,  1.3,  1.4,  1.6,  1.8,  2,   2.2,  2.5, 2.8, 3,    3.2,
                        3.8,  4,    4.5,  5,    5.5,  5.6,  6,    6.3,  7,   8,    9,   10};

 public:
  int stage = GENERATION;

  explicit State() = default;

  const double* GetRangeD() const {
    return range_d;
  }

  const std::vector<Entity*>& GetActors() const {
    return actors_;
  }

  const std::vector<Entity*>& GetSurvivors() const {
    return survivors_;
  }

  const std::vector<Entity*>& GetDescendants() const {
    return descendants_;
  }

  void AddActor(Entity* actor) {
    actors_.emplace_back(actor);
  }

  void AddSurvivor(Entity* survivor) {
    survivors_.emplace_back(survivor);
  }

  void AddDescendant(Entity* descendant) {
    descendants_.emplace_back(descendant);
  }

  void ReplaceDescendant(int index, Entity* entity) {
    descendants_[index] = entity;
  }

  void ClearActors() {
    actors_.clear();
    solutionId_ = -1;
  }

  void ClearSurvivors() {
    survivors_.clear();
  }

  void ClearDescendants() {
    descendants_.clear();
  }

  int GetGenerationNumber() {
    return generation_;
  }

  void IncGeneration() {
    generation_++;
  }

  void SortActors() {
    sort(actors_.begin(), actors_.end(), [](const auto& lhs, const auto& rhs) {
      return lhs->template Get<FitnessComponent>()->value_ < rhs->template Get<FitnessComponent>()->value_;
    });  // N*log2(N)
  }

  size_t GetSolutionId() const {
    return solutionId_;
  }

  void SetSolutionId(size_t solutionId) {
    solutionId_ = solutionId;
  }

  void SetAverageFitness(double avg) {
    averageFitness_ = avg;
  }

  double GetAverageFitness() const {
    return averageFitness_;
  }

  void SelectSurvivors(double Pc) {
    auto last = actors_.begin() + std::round(actors_.size() * (1 - Pc));
    survivors_.insert(survivors_.begin(), actors_.begin(), last);
  }

  void ExtractSurvivors(double Pc) {
    auto last = actors_.begin() + std::round(actors_.size() * (1 - Pc));
    actors_.erase(actors_.begin(), last);
  }

  void AddSurvivors() {
    actors_.insert(actors_.begin(), survivors_.begin(), survivors_.end());
  }

  void AddDescendants() {
    actors_.insert(actors_.end(), descendants_.begin(), descendants_.end());
  }

  void ShuffleActors() {
    auto rng = std::default_random_engine{rd_()};
    std::shuffle(actors_.begin(), actors_.end(), rng);
  }

  int GetGenerationLimit() const {
    return generationLimit_;
  }

  void SetGenerationLimit(int generationLimit) {
    generationLimit_ = generationLimit;
  }
};

#endif  // INCLUDE_SPRING_STATE_H_
