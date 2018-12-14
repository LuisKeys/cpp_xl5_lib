#pragma once
#include <iostream>

inline int xl5ml_sigmoid(int value) {
  return (int)(1.0 / (1.0 + exp(-value)));
}

inline float xl5ml_sigmoid(float value) {
  return (float)(1.0 / (1.0 + exp(-value)));
}

inline double xl5ml_sigmoid(double value) {
  return (double)(1.0 / (1.0 + exp(-value)));
}
