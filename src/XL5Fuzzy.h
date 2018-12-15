#pragma once

#include <iostream>

class XL5Fuzzy {
  public:
    float triangular_membership(float x, float center_x, float width) {

      // std::cout << "x" << '\n';
      // std::cout << x << '\n';
      //
      // std::cout << "center_x" << '\n';
      // std::cout << center_x << '\n';
      //
      // std::cout << "width" << '\n';
      // std::cout << width << '\n';

      float half_width = width / 2.0;
      float x1 = center_x - half_width;
      float x2 = center_x + half_width;
      float y;
      float m = 1.0 / half_width;
      float b;

      if(width == 0) {
        return 0;
      }

      if(x < center_x) {
        b = -m * x1;
        y = m * x + b;
      }
      else {
        b = m * x2;
        y = -m * x + b;
      }

      if(y < 0) {
        y = 0;
      }

      return y;
    }
};
