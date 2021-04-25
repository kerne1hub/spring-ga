//
// Created by kernel on 25.04.2021.
//

#ifndef INCLUDE_SPRING_COMPONENTS_FITNESS_COMPONENT_H_
#define INCLUDE_SPRING_COMPONENTS_FITNESS_COMPONENT_H_

#include <lib/ecs/component.h>

class FitnessComponent : public IComponent {
 public:
  double value_{};
  double fi1_{};
  double fi2_{};
  double fi3_{};
  double fi4_{};

  FitnessComponent() = default;

  explicit FitnessComponent(double value) : value_(value) {}
};

#endif  // INCLUDE_SPRING_COMPONENTS_FITNESS_COMPONENT_H_
