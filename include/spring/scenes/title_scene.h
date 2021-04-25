#ifndef INCLUDE_SPRING_SCENES_TITLE_SCENE_H_
#define INCLUDE_SPRING_SCENES_TITLE_SCENE_H_

#include <lib/scenes/i_scene.h>
#include <spring/controls.h>

#include <map>
#include <string>

class TitleScene : public IScene {
  const Controls& controls_;
  const std::string description_ =
      "Требуется минимизировать объем (вес) стальной проволоки, необходимый для изготовления одной пружины с заданными "
      "свойствами:\nF2 – заданное рабочее усилие, Н;\nH – размер (длина) пружины в свободном состоянии, м;\nh – "
      "величина статической деформации пружины, м;\nD – наружный диаметр пружины, мм;\n";

  int frame_left_ = 54;
  int frame_top_ = 3;
  int frame_width_ = 44;
  int frame_height_ = 24;

 public:
  TitleScene(Context* ctx, const Controls& controls);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;

 private:
  void Draw();
};

#endif  // INCLUDE_SPRING_SCENES_TITLE_SCENE_H_
