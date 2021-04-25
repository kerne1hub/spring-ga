#ifndef INCLUDE_LIB_SCENES_CONTEXT_H_
#define INCLUDE_LIB_SCENES_CONTEXT_H_

#include <lib/scenes/parameter.h>

#include <map>
#include <memory>
#include <string>

/**
 * В контексте хранится информация о сцене, которую нужно сейчас отрисоватывать.
 * Контекст должен создаться где-то во вне и передаться по указателю во все сцены,
 * чтобы они могли им манипулировать и в SceneManager,
 * чтобы он мог читать из него информацию о сценах.
 *
 * Кстати, можно использовать контекст для хранения некоторой информации при переходе между сценами.
 * Но рекомендуется придумать механизм, чтобы не пришлось постоянно править класс контектса.
 * Как минимум используйте map<string, iobject*>
 */
class Context {
 private:
  std::map<std::string, std::unique_ptr<IParameter>> params;

 public:
  void Init() {
    params["scene"] = std::make_unique<Parameter<std::string>>("title");
  }

  template<typename P>
  IParameter* Add(const std::string& name, P args) {
    params[name] = std::make_unique<Parameter<P>>(Parameter<P>(args));
    return params[name].get();
  }

  template<typename P>
  P Get(const std::string& name) const {
    auto param = params.at(name).get();
    auto value = (Parameter<P>*) (param);
    return value->GetValue();
  }

  bool Contains(const std::string& name) const {
    return params.count(name) != 0;
  }

  void Clear() {}
};

#endif  // INCLUDE_LIB_SCENES_CONTEXT_H_
