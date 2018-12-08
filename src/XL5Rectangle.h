#pragma once

#include <iostream>

template<class T>
class XL5Rectangle {
  public:
    XL5Rectangle() { }

    XL5Rectangle(T left, T top, T right, T bottom) {
      _left = left;
      _top = top;
      _right = right;
      _bottom = bottom;
    }

    T get_left() {
      return _left;
    }

    T get_top() {
      return _top;
    }

    T get_right() {
      return _right;
    }

    T get_bottom() {
      return _bottom;
    }

    void set_left(T left) {
      _left = left;
    }

    void set_top(T top) {
      _top = top;
    }

    void set_right(T right) {
      _right = right;
    }

    void set_bottom(T bottom) {
      _bottom = bottom;
    }

  private:
    T _left = 0;
    T _top = 0;
    T _right = 0;
    T _bottom = 0;
};
