#pragma once

#include <iostream>
#include "../XL5Log.h"
#include "../XL5Matrix.h"

class TestXL5Matrix {
	public:
		void test(int verbose) {
		 	XL5Log log;
			log.function_end("Test matrix (XL5Matrix) Passed Ok", XL5Color::BG_GREEN);
		}
};
