#pragma once
#include <iostream>
#include <iomanip>
#include <tuple>
#include <stdexcept>
#include "XL5Exceptions.h"
#include "XL5Log.h"
#include "XL5Memory.h"
#include "XL5Rectangle.h"

// matrix object and related operations
template<class T>
class XL5Matrix {
	public:
		// create a matrix object with given rows and cols
		void create(int rows_count, int cols_count, T constant) {
			XL5Memory::new_object();
			_matrix_elements = (T*)malloc(sizeof(T) * rows_count * cols_count);
			_rows_count = rows_count;
			_cols_count = cols_count;
			for(int i = 0; i < _rows_count * _cols_count; ++i)
				_matrix_elements[i] = constant;
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

			XL5Memory::new_object();
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

			XL5Memory::new_object();
			XL5Matrix<T>* C = new XL5Matrix<T>();

			C->create(c_rows_count, c_cols_count, 0);

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

			XL5Memory::new_object();
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
			int n = _rows_count;

			XL5Memory::new_object();
			XL5Matrix * Ainv = new XL5Matrix();
			Ainv->create(n, n, 0);

			XL5Memory::new_object();
			XL5Matrix * I = new XL5Matrix();
			I->create(n, n, 0);
			I->init_unit();

			XL5Memory::new_object();
			T* i = new T[n];

			for(int col = 0; col < n; ++col) {
				for(int row = 0; row < n; ++row) {
					i[row] = I->get(row, col);
				}

				XL5Matrix<double>* L;
				XL5Matrix<double>* U;
				int* pi;
				tie(pi, L, U) = lup_decomposition();

				T* x = lup_solve(L, U, pi, i);

				for(int row = 0; row < n; ++row) {
					Ainv->set(row, col, x[row]);
				}

				L->drop();
				U->drop();

				XL5Memory::delete_object();
				delete L;
				XL5Memory::delete_object();
				delete U;
				XL5Memory::delete_object();
				delete pi;
			}

			I->drop();
			XL5Memory::delete_object();
			delete I;

			return Ainv;
		}

		// multiply 2 matrices entry wise (Hadamard) AxB = C (Current is A and provided is B, and return a pointer to C)
		XL5Matrix<T> * clone() {
			XL5Memory::new_object();
			XL5Matrix<T> * Ac = new XL5Matrix<T>();
			Ac->create(_rows_count, _cols_count, 0);
			for(int row = 0; row < _rows_count; ++row) {
				for(int col = 0; col < _cols_count; ++col) {
					Ac->set(row, col, get(row, col));
				}
			}

			return Ac;
		}

		// LU decomposition returns a tuple with <L, U> matrices
		tuple<XL5Matrix<T> *, XL5Matrix<T> *> lu_decomposition() {
			int n = _rows_count;
			XL5Memory::new_object();
			XL5Matrix<T> * L = new XL5Matrix<T>();
			XL5Memory::new_object();
			XL5Matrix<T> * U = new XL5Matrix<T>();
			XL5Memory::new_object();
			XL5Matrix<T> * Ac = new XL5Matrix<T>();
			L->create(n, n);
			U->create(n, n);
			L->init_unit();
			U->init_constant(0);
			Ac = clone();

			for(int k = 0; k <n; ++k) {
					U->set(k, k, Ac->get(k, k));
					for(int i = k + 1; i < n; ++i) {
						float a_div_u = (float)Ac->get(i, k) / (float)U->get(k, k);
						L->set(i, k, (T)a_div_u);
						U->set(k, i, Ac->get(k, i));
					}

					for(int i = k + 1; i < n; ++i) {
						for(int j = k + 1; j < n; ++j) {
							float a = Ac->get(i, j) - L->get(i, k) * U->get(k, j);
							Ac->set(i, j, a);
						}
					}
			}

			Ac->drop();
			XL5Memory::delete_object();
			delete Ac;

			return  make_tuple(L, U);
		}

		// LUP decomposition returns a tuple with <L, U> matrices and pi vector
		tuple<int *, XL5Matrix<T> *, XL5Matrix<T> *> lup_decomposition() {
			int n = _rows_count;
			XL5Memory::new_object();
			XL5Matrix<T> * L = new XL5Matrix<T>();
			XL5Memory::new_object();
			XL5Matrix<T> * U = new XL5Matrix<T>();
			L->create(n, n, 0);
			U->create(n, n, 0);
			L->init_unit();
			U->init_constant(0);

			XL5Matrix<T> * Ac;
			Ac = clone();

			int * pi = new int[n];
			T p = 0;
			int kp = 0;
			int exchange_pi = 0;
			T exchange_a = 0;


			for(int i = 0; i < n; ++i) {
				pi[i] = i;
			}

			for(int k = 0; k < n; ++k) {
				p = 0;
				for(int i = k; i < n; ++i) {
						T abs_a = abs(Ac->get(i, k));
						if(abs_a > p) {
							p = abs_a;
							kp = i;
						}
				}

				if(p == 0) {
					xl5_exc_singular_matrix();
				}

				exchange_pi = pi[k];
				pi[k] = pi[kp];
				pi[kp] = exchange_pi;

				for(int i = 0; i < n; ++i) {
					exchange_a = Ac->get(k, i);
					Ac->set(k, i, Ac->get(kp, i));
					Ac->set(kp, i, exchange_a);
				}

				for(int i = k + 1; i < n; ++i) {
					T a_ik_div_a_kk = Ac->get(i, k) / Ac->get(k, k);
					Ac->set(i, k, a_ik_div_a_kk);
					for(int j = k + 1; j < n; ++j) {
							Ac->set(i, j, Ac->get(i, j) - Ac->get(i, k) * Ac->get(k, j));
					}
				}
			}

			for(int row = 0; row < _rows_count; ++row) {
				for(int col = 0; col < _cols_count; ++col) {
					T a = Ac->get(row, col);
					if(row > col) {
						L->set(row, col, a);
					}
					else {
						U->set(row, col, a);
					}
				}
			}

			Ac->drop();
			XL5Memory::delete_object();
			delete Ac;

			return  make_tuple(pi, L, U);
		}

		// LUP solve
		T* lup_solve(XL5Matrix<T> * L, XL5Matrix<T> * U, int* pi, T* b) {
			int n = L->rows_count();
			T* x = new T[n];
			T* y = new T[n];
			for(int i = 0; i < n; ++i) {
				double sum_l_y = 0;
				for(int j = 0; j < i; ++j) {
					sum_l_y += L->get(i, j) * y[j];
				}
				y[i] = b[pi[i]] - (T)sum_l_y;
			}

			for(int i = n - 1; i >= 0; --i) {
				double sum_u_x = 0;
				for(int j = i; j < n; ++j) {
					sum_u_x += U->get(i, j) * x[j];
				}
				x[i] = (y[i] - sum_u_x) / U->get(i, i);
			}

			XL5Memory::delete_object();
			delete y;

			return x;
		}

		// Render a rectangle
		void render_rectangle(XL5Rectangle<int>* rectangle, T value) {
			for(int col = rectangle->get_left(); col <= rectangle->get_right(); ++col) {
				set(rectangle->get_top(), col, value);
				set(rectangle->get_bottom(), col, value);
			}

			for(int row = rectangle->get_top(); row <= rectangle->get_bottom(); ++row) {
				set(row, rectangle->get_left(), value);
				set(row, rectangle->get_right(), value);
			}
		}

		// drop the matrix from memory
		void drop() {
			XL5Memory::delete_object();
			XL5Memory::delete_object();
			free(_matrix_elements);
			_rows_count = 0;
			_cols_count = 0;
		}

		// Write a matrix with a partial of its first and last elements to the console
		void log(const string& description, int color, int decimals) {

			cout << "\033[" << color << "m" << description << "\033[0m" << endl;

			cout << "\033[" << color << "m" << "Rows:" << _rows_count << "\033[0m" << endl;
			cout << "\033[" << color << "m" << "Cols:" << _cols_count << "\033[0m" << endl;

			for(int row = 0; row < _rows_count; ++row) {
				for(int col = 0; col < _cols_count; ++col) {
					cout << "\033[" << color << "m" << fixed << setprecision(decimals) << get(row, col) << "\t";
				}

				cout << endl	;
			}

			cout << "\033[" << color << "m" << "\033[0m" << endl;

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
