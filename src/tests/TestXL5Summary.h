#pragma once

#include <iostream>
#include "../XL5Log.h"
#include "../XL5Summary.h"

class TestXL5Summary {
	public:
		void test(int verbose) {
		 	XL5Log log;
		 	XL5Summary summary;

			int num_elements = 1000;
			float* numbers = new float[num_elements];

			for(int i = num_elements; i >= 0; --i) numbers[num_elements - i - 1] = i;

			if(verbose)
				log.array("Array to find max", numbers, num_elements, XL5Color::FG_DEFAULT);

			float max = summary.max(numbers, num_elements);

			if(verbose)
				log.value("number of elements:", num_elements, XL5Color::FG_DEFAULT);

			if(verbose)
				log.value("Max value:", max, XL5Color::FG_DEFAULT);

			if(max != num_elements - 1){
				log.function_end("Test Max (XL5Summary) Failed!", XL5Color::BG_RED);
				return;
			}

			log.function_end("Test Max (XL5Summary) Passed Ok", XL5Color::BG_GREEN);

			if(verbose)
				log.array<float>("Array to find min", numbers, num_elements, XL5Color::FG_DEFAULT);

			float min = summary.min(numbers, num_elements);

			if(verbose)
				log.value("number of elements:", num_elements, XL5Color::FG_DEFAULT);

			if(verbose)
				log.value("Min value:", min, XL5Color::FG_DEFAULT);

			if(min != 0){
				log.function_end("Test Min (XL5Summary) Failed!", XL5Color::BG_RED);
				return;
			}

			log.function_end("Test min (XL5Summary) Passed Ok", XL5Color::BG_GREEN);

		}

};
