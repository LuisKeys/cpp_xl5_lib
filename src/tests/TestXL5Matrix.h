#pragma once

#include <iostream>
#include "../XL5Log.h"
#include "../XL5Matrix.h"

class TestXL5Matrix {
	public:
		void test(int verbose) {
		 	XL5Log log;
			XL5Matrix<double> A;
			XL5Matrix<double> B;
			int rows = 4;
			int cols = 4;
			// Test matrix creation and initialize ops
			A.create(rows, cols);
			B.create(rows, cols);

			A.init_unit();

			if(verbose)
				A.log("Matrix A > init to unit", XL5Color::FG_YELLOW, 2);

			A.init_constant(2);

			if(verbose)
				A.log("Matrix A > init to 2", XL5Color::FG_YELLOW, 2);

				A.set(0, 0, 1);
				A.set(1, 0, 3);
				A.set(1, 1, 4);

				if(verbose)
					A.log("Matrix A > modified", XL5Color::FG_YELLOW, 2);

				A.drop();

				// Test LU decomposition

				rows = 3;
				cols = 3;

				A.create(rows, cols);

				// Sample from Cormen page 818
				A.set(0, 0, 1);
				A.set(0, 1, 2);
				A.set(0, 2, 0);

				A.set(1, 0, 3);
				A.set(1, 1, 4);
				A.set(1, 2, 4);

				A.set(2, 0, 5);
				A.set(2, 1, 6);
				A.set(2, 2, 3);

				int* pi_calc = A.lup_decomposition();

				if(verbose) {
					A.log("Matrix A > init for Cormen sample p. 818", XL5Color::FG_YELLOW, 2);
					log.array<int>("pi Array", pi_calc, rows, XL5Color::FG_DEFAULT);
				}

				delete pi_calc;

				XL5Matrix<double>* L;
				XL5Matrix<double>* U;

				std::tie(L, U) = A.lu_decomposition();

				L->log("Matrix L", XL5Color::FG_YELLOW, 3);
				U->log("Matrix U", XL5Color::FG_YELLOW, 3);

				L->drop();
				U->drop();
				A.drop();

				delete L;
				delete U;

				// Test LUP solve
				int* pi = new int[3];
				double* b = new double[3];

				rows = 3;
				cols = 3;

				L = new XL5Matrix<double>();
				U = new XL5Matrix<double>();

				A.create(rows, cols);
				L->create(rows, cols);
				U->create(rows, cols);

				// Sample from Cormen page 818
				A.set(0, 0, 1);
				A.set(0, 1, 2);
				A.set(0, 2, 0);

				A.set(1, 0, 3);
				A.set(1, 1, 4);
				A.set(1, 2, 4);

				A.set(2, 0, 5);
				A.set(2, 1, 6);
				A.set(2, 2, 3);

				b[0] = 3;
				b[1] = 7;
				b[2] = 8;

				L->set(0, 0, 1);
				L->set(0, 1, 0);
				L->set(0, 2, 0);

				L->set(1, 0, 0.2);
				L->set(1, 1, 1);
				L->set(1, 2, 0);

				L->set(2, 0, 0.6);
				L->set(2, 1, 0.5);
				L->set(2, 2, 1);

				U->set(0, 0, 5);
				U->set(0, 1, 6);
				U->set(0, 2, 3);

				U->set(1, 0, 0);
				U->set(1, 1, 0.8);
				U->set(1, 2, -0.6);

				U->set(2, 0, 0);
				U->set(2, 1, 0);
				U->set(2, 2, 2.5);

				pi[0] = 2;
				pi[1] = 0;
				pi[2] = 1;

				double* x = A.lup_solve(L, U, pi, b);

				if(verbose) {
					A.log("Matrix A > init for Cormen sample p. 818", XL5Color::FG_YELLOW, 2);
					L->log("Matrix L > init for Cormen sample p. 818", XL5Color::FG_YELLOW, 2);
					U->log("Matrix U > init for Cormen sample p. 818", XL5Color::FG_YELLOW, 2);
					log.array<int>("pi Array", pi, rows, XL5Color::FG_DEFAULT);
					log.array<double>("resulting x Array", x, rows, XL5Color::FG_DEFAULT);
				}

				L->drop();
				U->drop();

				delete L;
				delete U;
				delete pi;
				delete b;

				// A.traspose();
				//
				// if(verbose)
				// 	A.log("Matrix A > transposed", XL5Color::FG_YELLOW);
				//
				// B.init_random(1, 10);
				//
				// if(verbose)
				// 	B.log("Matrix B", XL5Color::FG_YELLOW);
				//
				// XL5Matrix<double>* C = A.multiply(&B);
				//
				// if(verbose)
				// 	C->log("Matrix C", XL5Color::FG_YELLOW);
				//
				// C->multiply(2);
				//
				// if(verbose)
				// 	C->log("Matrix C * 2", XL5Color::FG_YELLOW);
				//
				// XL5Matrix<double>* D = A.multiply_entry_wise(&A);
				//
				// if(verbose)
				// 	D->log("Matrix D", XL5Color::FG_YELLOW);


				A.drop();
				B.drop();
				// C->drop();
				// D->drop();

				// delete C;
				// delete D;

			log.function_end("Test matrix (XL5Matrix) Passed Ok", XL5Color::BG_GREEN);
		}
};
