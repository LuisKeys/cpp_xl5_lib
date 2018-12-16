#pragma once

#include <iostream>
#include <random>

using namespace std;

// ranomd handy functions
template<class T>
class  XL5Random{
  public:
    void init() {
      srand((unsigned)time(0));
    }

    T get_value(T min, T max) {
      return (T)((max - min) * ((float)rand() / RAND_MAX)) + min;
      // cout << fixed << setprecision(5) << setw(2) << value << endl;
    }
};
