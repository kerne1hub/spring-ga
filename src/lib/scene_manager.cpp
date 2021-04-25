#include <lib/scenes/scene_manager.h>

#include <string>

void SceneManager::OnRender() {
  if (ctx_.Get<std::string>("scene") != current_scene_) {
    printf("Transition from '%s' to '%s'\n", current_scene_.data(), ctx_.Get<std::string>("scene").data());
    if (scenes_.count(current_scene_) != 0) {
      scenes_.at(current_scene_)->OnExit();
    }
    current_scene_ = ctx_.Get<std::string>("scene");
    scenes_.at(current_scene_)->OnCreate();
  }
  if (scenes_.count(current_scene_) != 0) {
    scenes_.at(current_scene_)->OnRender();
  } else {
    printf("[WARNING] Cannot update scene_ '%s': it doesn't exist.", current_scene_.data());
  }
}

void SceneManager::OnExit() const {
  if (scenes_.count(current_scene_) != 0) {
    scenes_.at(current_scene_)->OnExit();
  }
}
void SceneManager::Put(const std::string& name, IScene* const scene) {
  scenes_[name] = std::unique_ptr<IScene>(scene);
}
SceneManager::SceneManager(const Context& ctx) : ctx_(ctx) {}
