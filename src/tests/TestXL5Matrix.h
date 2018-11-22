#pragma once

#include <iostream>
#include "../XL5Log.h"
#include "../XL5Matrix.h"

class TestXL5Matrix {
	public:
		void test(int verbose) {
		 	XL5Log log;
			XL5Matrix<float> A;
			int rows = 4;
			int cols = 2;

			A.create(rows, cols);

			A.init_constant(2);

			if(verbose)
				A.log("Matrix A > init to 2", XL5Color::FG_YELLOW);

				A.set(0, 0, 1);
				A.set(1, 0, 3);
				A.set(1, 1, 4);

				if(verbose)
					A.log("Matrix A > modified", XL5Color::FG_YELLOW);

				A.traspose();

				if(verbose)
					A.log("Matrix A > transposed", XL5Color::FG_YELLOW);

				A.init_unit();

				if(verbose)
					A.log("Matrix A > init to unit", XL5Color::FG_YELLOW);

				A.drop();

			log.function_end("Test matrix (XL5Matrix) Passed Ok", XL5Color::BG_GREEN);
		}
};
