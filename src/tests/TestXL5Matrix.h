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

				rows = 4;
				cols = 4;

				A.create(rows, cols);

				// Sample from Cormen page 822
				A.set(0, 0, 2);
				A.set(0, 1, 3);
				A.set(0, 2, 1);
				A.set(0, 3, 5);

				A.set(1, 0, 6);
				A.set(1, 1, 13);
				A.set(1, 2, 5);
				A.set(1, 3, 19);

				A.set(2, 0, 2);
				A.set(2, 1, 19);
				A.set(2, 2, 10);
				A.set(2, 3, 23);

				A.set(3, 0, 4);
				A.set(3, 1, 10);
				A.set(3, 2, 11);
				A.set(3, 3, 31);

				if(verbose)
					A.log("Matrix A > init for Cormen sample p. 822", XL5Color::FG_YELLOW, 2);

				XL5Matrix<double>* L;
				XL5Matrix<double>* U;

				std::tie(L, U) = A.lu_decomposition();

				L->log("Matrix L", XL5Color::FG_YELLOW, 3);
				U->log("Matrix U", XL5Color::FG_YELLOW, 3);

				if(verbose)
					A.log("Matrix A > init for Cormen sample p. 822", XL5Color::FG_YELLOW, 2);

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
