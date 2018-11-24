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
			int rows = 2;
			int cols = 2;

			A.create(rows, cols);
			B.create(rows, cols);

			A.init_unit();

			if(verbose)
				A.log("Matrix A > init to unit", XL5Color::FG_YELLOW);

			A.init_constant(2);

			if(verbose)
				A.log("Matrix A > init to 2", XL5Color::FG_YELLOW);

				A.set(0, 0, 1);
				A.set(1, 0, 3);
				A.set(1, 1, 4);

				if(verbose)
					A.log("Matrix A > modified", XL5Color::FG_YELLOW);

				A.drop();

				rows = 2;
				cols = 4;

				A.create(rows, cols);

				A.init_random(1, 10);

				if(verbose)
					A.log("Matrix A > init to random from 1 to 10", XL5Color::FG_YELLOW);

				A.traspose();

				if(verbose)
					A.log("Matrix A > transposed", XL5Color::FG_YELLOW);

				B.init_random(1, 10);

				if(verbose)
					B.log("Matrix B", XL5Color::FG_YELLOW);

				XL5Matrix<double>* C = A.multiply(&B);

				if(verbose)
					C->log("Matrix C", XL5Color::FG_YELLOW);

				C->multiply(2);

				if(verbose)
					C->log("Matrix C * 2", XL5Color::FG_YELLOW);

				XL5Matrix<double>* D = A.multiply_entry_wise(&A);

				if(verbose)
					D->log("Matrix D", XL5Color::FG_YELLOW);

				A.drop();
				B.drop();
				C->drop();
				D->drop();

				delete C;
				delete D;

			log.function_end("Test matrix (XL5Matrix) Passed Ok", XL5Color::BG_GREEN);
		}
};
