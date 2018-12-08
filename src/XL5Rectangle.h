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

  private:
    T _left = 0;
    T _top = 0;
    T _right = 0;
    T _bottom = 0;
};
