#pragma once

#include <stdexcept>
#include "XL5Log.h"

inline void exc_matrix_not_square() {
  XL5Log log;
  log.exception_msg("Matrix is not square");
  throw std::exception();
}

inline void exc_index_out_of_range(int row, int col) {
  XL5Log log;
  log.exception_msg("Index out of range");
  log.value("Row:", row, XL5Color::FG_BLUE);
  log.value("Col:", col, XL5Color::FG_BLUE);
  throw std::exception();
}
