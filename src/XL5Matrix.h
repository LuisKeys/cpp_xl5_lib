#pragma once
#include <iostream>
#include <tuple>
#include <stdexcept>
#include "XL5Exceptions.h"
#include "XL5Log.h"

// matrix object and related operations
template<class T>
class XL5Matrix {
	public:
		// create a matrix object with given rows and cols
		void create(int rows_count, int cols_count) {
			_matrix_elements = (T*)malloc(sizeof(T) * rows_count * cols_count);
			_rows_count = rows_count;
			_cols_count = cols_count;
			for(int i = 0; i < _rows_count * _cols_count; ++i)
				_matrix_elements[i] = 0;
		}

		// initialize the matrix with a constant value
		void init_constant(T value) {
			for(int row = 0; row < _rows_count; ++row) {
				for(int col = 0; col < _cols_count; ++col) {
					_matrix_elements[get_index(row, col)] = value;
				}
			}
		}

		// initialize a unit matrix
		void init_unit() {
			if (_rows_count != _cols_count) {
				xl5_exc_matrix_not_square();
			}

			for(int row = 0; row < _rows_count; ++row) {
				for(int col = 0; col < _cols_count; ++col) {
					if(row == col)
						_matrix_elements[get_index(row, col)] = 1;
					else
					_matrix_elements[get_index(row, col)] = 0;
				}
			}
		}

		// initialize a random matrix
		void init_random(T min, T max) {
			srand((unsigned)time(0));

			for(int row = 0; row < _rows_count; ++row) {
				for(int col = 0; col < _cols_count; ++col) {\
						T i = (T)((int)((T)rand()) % (int)((T)max)) + (T)min;
						_matrix_elements[get_index(row, col)] = i;
				}
			}
		}

		// matrix vert size
		int rows_count() {
			return _rows_count;
		}

		// matrix horiz size
		int cols_count() {
			return _cols_count;
		}

		// get a matrix element
		T get(int row, int col) {
			return _matrix_elements[get_index(row, col)];
		}

		// set a matrix element
		T set(int row, int col, T value) {
			_matrix_elements[get_index(row, col)] = value;
		}

		// traspose matrix
		void traspose() {
			int t_cols_count = _rows_count;
			int t_rows_count = _cols_count;

			T* t_matrix_elements = (T*)malloc(sizeof(T) * _rows_count * _cols_count);
			for(int row = 0; row < _rows_count; ++row) {
				for(int col = 0; col < _cols_count; ++col) {
						t_matrix_elements[get_index_no_check(col, row, t_cols_count)] = _matrix_elements[get_index(row, col)];
				}
			}

			void drop();

			_matrix_elements = t_matrix_elements;

			_cols_count = t_cols_count;
			_rows_count = t_rows_count;
		}

		// multiply 2 matrices AxB = C (Current is A and provided is B, and return a pointer to C)
		XL5Matrix<T> * multiply(XL5Matrix<T>* B) {
			if(_cols_count != B->rows_count()) {
				xl5_exc_cannot_multiply_matrices(_cols_count, B->cols_count());
			}
			int c_rows_count = _rows_count;
			int c_cols_count = B->cols_count();

			XL5Matrix<T>* C = new XL5Matrix<T>();

			C->create(c_rows_count, c_cols_count);

			for(int c_row = 0; c_row < c_rows_count; ++c_row) {
				for(int c_col = 0; c_col < c_cols_count; ++c_col) {
						T sum = 0;
						for( int a_col = 0; a_col < _cols_count; ++a_col) {
							T a = _matrix_elements[get_index(c_row, a_col)];
							T b = B->get(a_col, c_col);
							sum += a * b;
						}

						C->set(c_row, c_col, sum);
				}
			}

			return C;
		}

		// multiply matrix elements by a constant
		void multiply(T coeficient) {
			for(int row = 0; row < _rows_count; ++row) {
				for(int col = 0; col < _cols_count; ++col) {
						_matrix_elements[get_index(row, col)] *= coeficient;
				}
			}
		}

		// multiply 2 matrices entry wise (Hadamard) AxB = C (Current is A and provided is B, and return a pointer to C)
		XL5Matrix<T> * multiply_entry_wise(XL5Matrix<T>* B) {
			if((_cols_count != B->cols_count()) || (_rows_count != B->rows_count())) {
				xl5_exc_cannot_multiply_entry_wise_matrices(_cols_count, _rows_count, B->cols_count(), B->rows_count());
			}

			int c_rows_count = _rows_count;
			int c_cols_count = _cols_count;

			XL5Matrix<T>* C = new XL5Matrix<T>();

			C->create(c_rows_count, c_cols_count);

			for(int c_row = 0; c_row < c_rows_count; ++c_row) {
				for(int c_col = 0; c_col < c_cols_count; ++c_col) {
					T a = _matrix_elements[get_index(c_row, c_col)];
					T b = B->get(c_row, c_col);
					C->set(c_row, c_col, a * b);
				}
			}

			return C;
		}

		// multiply 2 matrices entry wise (Hadamard) AxB = C (Current is A and provided is B, and return a pointer to C)
		XL5Matrix<T> * invert() {
		}

		// LU decomposition returns a tuple with <L, U> matrices
		std::tuple<XL5Matrix<T> *, XL5Matrix<T> *> lu_decomposition() {
			int n = _rows_count;
			XL5Matrix<T> * L = new XL5Matrix<T>();
			XL5Matrix<T> * U = new XL5Matrix<T>();
			L.create(n, n);
			U.create(n, n);
			L.init_unit();
			U.init_constant(0);

			for(int k = 0; k <n; ++k) {
					U.set(k, k, get(k, k));
			}

			return  std::make_tuple(NULL, NULL);
		}

		// drop the matrix from memory
		void drop() {
			free(_matrix_elements);
			_rows_count = 0;
			_cols_count = 0;
		}

		// Write a matrix with a partial of its first and last elements to the console
		void log(const std::string& description, int color) {

			std::cout << "\033[" << color << "m" << description << "\033[0m" << std::endl;

			std::cout << "\033[" << color << "m" << "Rows:" << _rows_count << "\033[0m" << std::endl;
			std::cout << "\033[" << color << "m" << "Cols:" << _cols_count << "\033[0m" << std::endl;

			for(int row = 0; row < _rows_count; ++row) {
				for(int col = 0; col < _cols_count; ++col) {
					std::cout << "\033[" << color << "m" << get(row, col) << "\t";
				}

				std::cout << std::endl	;
			}

			std::cout << "\033[" << color << "m" << "\033[0m" << std::endl;

		}
	private:
		T* _matrix_elements;
		int _rows_count = 0;
		int _cols_count = 0;

		int get_index_no_check(int row, int col, int cols_count) {
			int index = row * cols_count + col;

			return index;
		}

		int get_index(int row, int col) {
			int index = row * _cols_count + col;

			if (index < 0 || index > _rows_count * _cols_count) {
				xl5_exc_index_out_of_range(row, col);
			}

			return index;
		}

};
