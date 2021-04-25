//
// Created by kernel on 25.04.2021.
//

#ifndef INCLUDE_SPRING_SCENES_MAIN_SCENE_H_
#define INCLUDE_SPRING_SCENES_MAIN_SCENE_H_

#include <lib/ecs/engine.h>
#include <lib/scenes/i_scene.h>
#include <lib/ui/page.h>
#include <spring/configuration.h>
#include <spring/controls.h>
#include <spring/state.h>

#include <map>
#include <vector>

class MainScene : public IScene {
  typedef void (MainScene::*key_method_t)();
  typedef std::map<int, key_method_t> key_func_map_t;

  const Engine engine{};
  const Controls& controls_;
  std::unique_ptr<Configuration> config_;
  State state{};
  std::vector<Page> pages_;
  key_func_map_t keyFuncMap_;

 public:
  MainScene(Context* ctx, const Controls& controls);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif  // INCLUDE_SPRING_SCENES_MAIN_SCENE_H_
