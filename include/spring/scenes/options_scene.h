#ifndef INCLUDE_SPRING_SCENES_OPTIONS_SCENE_H_
#define INCLUDE_SPRING_SCENES_OPTIONS_SCENE_H_

#include <lib/scenes/i_scene.h>
#include <lib/ui/page.h>
#include <lib/ui/text_field.h>
#include <spring/controls.h>

#include <map>
#include <string>
#include <vector>

class OptionsScene : public IScene {
  typedef void (OptionsScene::*key_method_t)();
  typedef std::map<int, key_method_t> key_func_map_t;

  const Controls& controls_;
  std::map<int, TextField> fields_;
  std::map<std::string, TextField*> labels_;
  std::vector<Page> pages_;
  key_func_map_t keyFuncMap_;
  int selectedField_ = 0;

 public:
  OptionsScene(Context* ctx, const Controls& controls);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;

 private:
  void Draw();
  void MoveUp();
  void MoveDown();
  void MoveRight();
  void MoveLeft();
  void Click();
};

#endif  // INCLUDE_SPRING_SCENES_OPTIONS_SCENE_H_
