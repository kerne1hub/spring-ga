//
// Created by kernel on 25.04.2021.
//
#include <BearLibTerminal.h>
#include <lib/ui/page.h>

void Page::Draw() {
  terminal_clear_area(x_, y_, width_, height_);

  for (int i = x_; i < x_ + width_; i++) {
    terminal_put(i, y_, L'─');
    terminal_put(i, y_ + height_ - 1, L'─');
  }

  terminal_print_ext(x_, y_, width_, 1, TK_ALIGN_CENTER | TK_ALIGN_MIDDLE,
                     title_.c_str());

  for (int j = y_; j < y_ + height_; j++) {
    terminal_put(x_, j, L'│');
    terminal_put(x_ + width_ - 1, j, L'│');
  }

  terminal_put(x_, y_, L'┌');
  terminal_put(x_ + width_ - 1, y_, L'┐');
  terminal_put(x_, y_ + height_ - 1, L'└');
  terminal_put(x_ + width_ - 1, y_ + height_ - 1, L'┘');

  terminal_color("white");
}
