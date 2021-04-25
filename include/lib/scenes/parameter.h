//
// Created by kernel on 29.07.2020.
//

#ifndef INCLUDE_LIB_SCENES_PARAMETER_H_
#define INCLUDE_LIB_SCENES_PARAMETER_H_

class IParameter {
 public:
  virtual ~IParameter() = default;
};

template<typename T>
class Parameter : public IParameter{
 private:
  T value;

 public:
  T GetValue() {
    return value;
  }
  explicit Parameter(T value) : value(value) {}
  ~Parameter() override = default;
};

#endif  // INCLUDE_LIB_SCENES_PARAMETER_H_
