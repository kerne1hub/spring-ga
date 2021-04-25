#include <BearLibTerminal.h>
#include <spring/configuration.h>
#include <spring/scenes/options_scene.h>

#include <string>

OptionsScene::OptionsScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}

void OptionsScene::OnCreate() {
  ctx_->Clear();

  pages_.emplace_back(1, 1, 52, 22, " Параметры модели");
  pages_.emplace_back(56, 1, 40, 22, " Параметры алгоритма");

  fields_.insert(std::make_pair(0, TextField{30, 3, 20, 3}));
  fields_.insert(std::make_pair(1, TextField{30, 6, 20, 3}));
  fields_.insert(std::make_pair(2, TextField{30, 9, 20, 3}));
  fields_.insert(std::make_pair(3, TextField{30, 12, 20, 3}));
  fields_.insert(std::make_pair(4, TextField{30, 15, 20, 3}));
  fields_.insert(std::make_pair(5, TextField{30, 18, 20, 3}));
  fields_.insert(std::make_pair(6, TextField{85, 3, 8, 3}));
  fields_.insert(std::make_pair(7, TextField{85, 6, 8, 3}));
  fields_.insert(std::make_pair(8, TextField{81, 24, 15, 3, "Продолжить"}));

  labels_.insert(std::make_pair("Рабочее усилие, Н", &fields_.at(0)));
  labels_.insert(std::make_pair("Длина пружины, м", &fields_.at(1)));
  labels_.insert(std::make_pair("Макс. напр. при круч., МПа", &fields_.at(2)));
  labels_.insert(std::make_pair("Модуль сдвига, МПа", &fields_.at(3)));
  labels_.insert(std::make_pair("Мин. внеш. диаметр D, мм", &fields_.at(4)));
  labels_.insert(std::make_pair("Макс. внеш. диаметр D, мм", &fields_.at(5)));
  labels_.insert(std::make_pair("Вероятность кроссовера Pc", &fields_.at(6)));
  labels_.insert(std::make_pair("Вероятность мутации Pм", &fields_.at(7)));
  labels_.insert(std::make_pair("", &fields_.at(8)));

  fields_.at(0).isSelected_ = true;

  keyFuncMap_[TK_DOWN] = &OptionsScene::MoveDown;
  keyFuncMap_[TK_UP] = &OptionsScene::MoveUp;
  keyFuncMap_[TK_RIGHT] = &OptionsScene::MoveRight;
  keyFuncMap_[TK_LEFT] = &OptionsScene::MoveLeft;
  keyFuncMap_[TK_ENTER] = &OptionsScene::Click;
}

void OptionsScene::OnRender() {
  terminal_clear();

  for (auto &page : pages_) {
    page.Draw();
  }

  for (auto &label : labels_) {
    auto x = label.second->GetX();
    auto y = label.second->GetY();
    terminal_printf(x - 28, y + 1, label.first.c_str());
    label.second->Draw();
    label.second->DrawText();
  }

  terminal_refresh();

  for (const auto &func : keyFuncMap_) {
    if (controls_.IsPressed(func.first)) {
      (this->*(func.second))();
    }
  }

  terminal_refresh();
}

void OptionsScene::OnExit() {
  fields_.clear();
  labels_.clear();
  pages_.clear();
  keyFuncMap_.clear();
  terminal_composition(TK_OFF);
}

void OptionsScene::Draw() {}

void OptionsScene::MoveDown() {
  if (selectedField_ < static_cast<int>(fields_.size()) - 1) {
    fields_.at(selectedField_).isSelected_ = false;
    fields_.at(++selectedField_).isSelected_ = true;
  }
}

void OptionsScene::MoveUp() {
  if (selectedField_ > 0) {
    fields_.at(selectedField_).isSelected_ = false;
    fields_.at(--selectedField_).isSelected_ = true;
  }
}

void OptionsScene::MoveRight() {
  if (selectedField_ < 6) {
    if (selectedField_ < 2) {
      fields_.at(selectedField_).isSelected_ = false;
      selectedField_ += 6;
      fields_.at(selectedField_).isSelected_ = true;
    } else {
      fields_.at(selectedField_).isSelected_ = false;
      selectedField_ = 6;
      fields_.at(selectedField_).isSelected_ = true;
    }
  }
}

void OptionsScene::MoveLeft() {
  if (selectedField_ > 5) {
    fields_.at(selectedField_).isSelected_ = false;
    selectedField_ -= 6;
    fields_.at(selectedField_).isSelected_ = true;
  }
}

void OptionsScene::Click() {
  if (selectedField_ == 8) {
    ctx_->Add<Configuration>("config", {std::stod(fields_.at(0).GetText()),
                                        std::stod(fields_.at(1).GetText()),
                                        std::stoi(fields_.at(2).GetText()),
                                        std::stoi(fields_.at(3).GetText()),
                                        std::stoi(fields_.at(4).GetText()),
                                        std::stoi(fields_.at(5).GetText()),
                                        std::stod(fields_.at(6).GetText()),
                                        std::stod(fields_.at(7).GetText())});
    ctx_->Add<std::string>("scene", "main");
  } else {
    fields_.at(selectedField_).TextInput();
  }
}
