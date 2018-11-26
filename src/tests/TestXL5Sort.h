#pragma once

#include <iostream>
#include "../XL5Log.h"
#include "../XL5Sort.h"

class TestXL5Sort {
	public:
		void test(int verbose) {
		 	XL5Log log;
		 	XL5Sort sort;

			int num_elements = 10;
			float* numbers = new float[num_elements];

			for(int i = num_elements; i >= 0; --i) numbers[num_elements - i - 1] = i;

			if(verbose)
				log.array<float>("Array to sort", numbers, num_elements, XL5Color::FG_DEFAULT);

			sort.sort(numbers, num_elements);

			if(verbose)
				log.value("number of elements:", num_elements, XL5Color::FG_DEFAULT);

			if(verbose)
				log.array<float>("Sorted", numbers, num_elements, XL5Color::FG_DEFAULT);


			for(int i = 0; i < num_elements; ++i) {
				float a = numbers[i];
				float b = i;
				if(a != b) {
					log.function_end("Test Merge Sort (XL5Sort) Failed!", XL5Color::BG_RED);
					return;
				}
			}

			log.function_end("Test Merge Sort (XL5Sort) Passed Ok", XL5Color::BG_GREEN);
		}
};
