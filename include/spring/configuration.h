//
// Created by kernel on 25.04.2021.
//

#ifndef INCLUDE_SPRING_CONFIGURATION_H_
#define INCLUDE_SPRING_CONFIGURATION_H_

class Configuration {
 private:
  double F2_;                         // Заданное рабочее усилие (Н)
  double H_;                          // Длина пружины в свободном состоянии (м)
  int T_KR_;                          // Допустимое напряжение кручения (Н/мм2)
  int G;                              // Модуль сдвига (Н/мм2)
  int minD_;
  int maxD_;
  double h_ = 0.01;

  double Pc_;
  double Pm_;

 public:
  Configuration(double f2, double h, int tKr, int g, int minD, int maxD, double Pc, double Pm)
      : F2_(f2), H_(h), T_KR_(tKr), G(g), minD_(minD), maxD_(maxD), Pc_(Pc), Pm_(Pm) {}

  double GetF2() const {
    return F2_;
  }

  double GetH() const {
    return H_;
  }

  int GetTKr() const {
    return T_KR_;
  }

  int GetG() const {
    return G;
  }

  double GetMinD() const {
    return minD_;
  }

  double GetMaxD() const {
    return maxD_;
  }

  double GetPc() const {
    return Pc_;
  }

  double GetPm() const {
    return Pm_;
  }

  double GetH3() const {
    return h_;
  }
};

#endif  // INCLUDE_SPRING_CONFIGURATION_H_
