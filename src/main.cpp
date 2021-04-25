#include <BearLibTerminal.h>
#include <lib/scenes/scene_manager.h>
#include <spring/controls.h>
#include <spring/scenes/main_scene.h>
#include <spring/scenes/options_scene.h>
#include <spring/scenes/title_scene.h>

int main() {
  terminal_open();
  terminal_set("window: title='Spring Optimization'; input: filter={keyboard}; window: size=100x30");
  terminal_refresh();

  Controls controls;

  Context ctx{};  // создаем контекст на стеке в самом начале приложения
  SceneManager sm(ctx);  // создаем менеджер сцен на стеке

  // Регистрируем сцены в менеджер. Обратите внимание,
  // что деструкторы над сценами вызывать здесь не надо, так как их вызовет менеджер.
  sm.Put("title", new TitleScene(&ctx, controls));
  sm.Put("options", new OptionsScene(&ctx, controls));
  sm.Put("main", new MainScene(&ctx, controls));

  // Выставляем текущую сцену
  ctx.Init();

  // Ждем, пока пользователь не закроет окно
  while (true) {
    controls.OnUpdate();
    if (controls.IsPressed(TK_CLOSE)) {
      break;
    }

    sm.OnRender();

    controls.Reset();
  }
  sm.OnExit();

  terminal_close();
}
