//
// Created by kernel on 19.08.2020.
//

#ifndef INCLUDE_SPRING_COMPONENTS_CHARACTERISTICS_COMPONENT_H_
#define INCLUDE_SPRING_COMPONENTS_CHARACTERISTICS_COMPONENT_H_

#include <lib/ecs/component.h>

#include <cmath>

class CharacteristicsComponent : public IComponent {
 public:
  int d_index_{};
  double d_{};
  double D_{};
  double m_{};
  double n_{};
  double t3_{};

  CharacteristicsComponent() = default;

  CharacteristicsComponent(int d_index, double d, double D, double F2, double G, double h)
      : d_index_(d_index), d_(d), D_(D) {
    m_ = D / d;
    double F3 = F2 / 0.75;
    t3_ = (((4 * m_) - 1) / (4 * m_ - 4) + (0.615 / m_)) * ((8 * F3 * D) / (3.14159 * pow(d, 3)));
    double c = F2 / h;
    n_ = std::round(((G * pow(d, 4)) / (8 * pow(D, 3) * c)) * 1000);
  }
};

#endif  // INCLUDE_SPRING_COMPONENTS_CHARACTERISTICS_COMPONENT_H_
