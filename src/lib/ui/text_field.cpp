//
// Created by kernel on 25.04.2021.
//
#include <BearLibTerminal.h>
#include <lib/ui/text_field.h>

#include <string>

void TextField::Draw() {
  terminal_clear_area(x_, y_, width_, height_);
  CheckState();

  for (int i = x_; i < x_ + width_; i++) {
    terminal_put(i, y_, L'─');
    terminal_put(i, y_ + height_ - 1, L'─');
  }

  for (int j = y_; j < y_ + height_; j++) {
    terminal_put(x_, j, L'│');
    terminal_put(x_ + width_ - 1, j, L'│');
  }

  terminal_put(x_, y_, L'┌');
  terminal_put(x_ + width_ - 1, y_, L'┐');
  terminal_put(x_, y_ + height_ - 1, L'└');
  terminal_put(x_ + width_ - 1, y_ + height_ - 1, L'┘');

  terminal_color(DEFAULT.c_str());
}
void TextField::CheckState() const {
  if (isActive_) {
    terminal_color(ACTIVE.c_str());
  } else if (isSelected_) {
    terminal_color(SELECTED.c_str());
  } else {
    terminal_color(DEFAULT.c_str());
  }
}

void TextField::TextInput() {
  isActive_ = true;
  Draw();
  terminal_read_str(x_ + 1, y_ + 1, buffer_, 16);

  isActive_ = false;
}

std::string TextField::GetText() {
  return std::string(buffer_);
}

void TextField::DrawText() {
  terminal_printf(x_ + 1, y_ + 1, L"%s", buffer_);
}

int TextField::GetX() const {
  return x_;
}

int TextField::GetY() const {
  return y_;
}

int TextField::GetWidth() const {
  return width_;
}

int TextField::GetHeight() const {
  return height_;
}
