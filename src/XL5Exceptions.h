#pragma once

#include <stdexcept>
#include "XL5Log.h"

using namespace std;
inline void xl5_exc_matrix_not_square() {
  XL5Log log;
  log.exception_msg("Matrix is not square");
  throw exception();
}

inline void xl5_exc_index_out_of_range(int row, int col) {
  XL5Log log;
  log.exception_msg("Index out of range");
  log.value("Row:", row, XL5Color::FG_BLUE);
  log.value("Col:", col, XL5Color::FG_BLUE);
  throw exception();
}

inline void xl5_exc_cannot_multiply_matrices(int a_cols, int b_rows) {
  XL5Log log;
  log.exception_msg("First matrix horiz size is different to second matrix vertical size hence they cannot be multiplied");
  log.value("A Cols", a_cols, XL5Color::FG_BLUE);
  log.value("B Rows", b_rows, XL5Color::FG_BLUE);
  throw exception();
}

inline void xl5_exc_cannot_multiply_entry_wise_matrices(int a_cols, int a_rows, int b_cols, int b_rows) {
  XL5Log log;
  log.exception_msg("Cannot multiply entry wise because the matrices are different");
  log.value("A Cols", a_cols, XL5Color::FG_BLUE);
  log.value("A Rows", a_rows, XL5Color::FG_BLUE);
  log.value("B Cols", b_cols, XL5Color::FG_BLUE);
  log.value("B Rows", b_rows, XL5Color::FG_BLUE);
  throw exception();
}

inline void xl5_exc_singular_matrix() {
  XL5Log log;
  log.exception_msg("Matrix is singular");
  throw exception();
}
