#include <BearLibTerminal.h>
#include <spring/scenes/title_scene.h>

#include <string>

TitleScene::TitleScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}

void TitleScene::OnCreate() {
  terminal_set("U+E000: ./resources/model.png");
  ctx_->Clear();
}

void TitleScene::OnRender() {
  terminal_clear();

  terminal_put(2, 2, 0xE000);

  // Background square
  terminal_bkcolor("darkest gray");
  terminal_clear_area(frame_left_, frame_top_, frame_width_, frame_height_);
  terminal_bkcolor("none");

  terminal_print_ext(frame_left_, frame_top_, frame_width_, frame_height_, TK_ALIGN_LEFT | TK_ALIGN_TOP,
                     description_.c_str());

  terminal_print(82, 28, "[c=green][U+005B]Enter[U+005D][/c] Continue");

  if (controls_.IsPressed(TK_ENTER)) {
    ctx_->Add<std::string>("scene", "options");
  }

  terminal_refresh();
}

void TitleScene::OnExit() {
  terminal_set("U+E000: none");
  terminal_composition(TK_OFF);
}

void TitleScene::Draw() {}
