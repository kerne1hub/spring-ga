//
// Created by kernel on 25.04.2021.
//

#ifndef INCLUDE_LIB_UI_PAGE_H_
#define INCLUDE_LIB_UI_PAGE_H_

#include <string>
#include <utility>
class Page {
 private:
  int x_;
  int y_;
  int width_;
  int height_;
  std::string title_;

 public:
  Page(int x, int y, int width, int height, std::string title)
      : x_(x), y_(y), width_(width), height_(height), title_(std::move(title)) {}

  void Draw();
};

#endif  // INCLUDE_LIB_UI_PAGE_H_
