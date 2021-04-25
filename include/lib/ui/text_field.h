//
// Created by kernel on 25.04.2021.
//

#ifndef INCLUDE_LIB_UI_TEXT_FIELD_H_
#define INCLUDE_LIB_UI_TEXT_FIELD_H_

#include <map>
#include <cstring>
#include <string>

class TextField {
 private:
  int x_;
  int y_;
  int width_;
  int height_;

  char buffer_[33] = {0};

 public:
  bool isSelected_ = false;
  bool isActive_ = false;

  const std::string ACTIVE = "green";
  const std::string SELECTED = "yellow";
  const std::string DEFAULT = "white";

  TextField(int x, int y, int width, int height) {
    x_ = x;
    y_ = y;
    width_ = width;
    height_ = height;
  }

  TextField(int x, int y, int width, int height, const std::string& text) {
    x_ = x;
    y_ = y;
    width_ = width;
    height_ = height;

    strncpy(buffer_, text.c_str(), 33);
  }

  void Draw();
  void DrawText();
  void TextInput();
  std::string GetText();
  int GetX() const;
  int GetY() const;
  int GetWidth() const;
  int GetHeight() const;
  void CheckState() const;
};

#endif  // INCLUDE_LIB_UI_TEXT_FIELD_H_
