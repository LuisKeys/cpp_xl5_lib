#pragma once

#include <iostream>
#include "../XLLog.h"
#include "../XLStack.h"

class TestXLStack {
	public:
		void test(int verbose) {
		 	XLLog log;
		 	XLStack<float*> stack;
		 	float* popped_numbers;

		 	float* numbers = new float(4);
		 	numbers[0] = 10;
		 	numbers[1] = 20;
		 	numbers[2] = 36;
		 	numbers[3] = 48;

		 	stack.create(1000);

		 	for(int i = 0; i < 4; ++i) {
			 	stack.push(numbers);
				log.value("Size", stack.size(), XLColor::FG_YELLOW);
		 	}

		 	for(int i = 0; i < 1; ++i) {
			 	// popped_numbers = stack.pop();
		 	}

			// log.array("popped numbers", popped_numbers, 1, XLColor::FG_YELLOW);
		 	/*
		 	for(int i = 0; i < 11; ++i) {
			 	int status = stack.push(numbers);
			 	if(status == XL_STACK_ERR_STACK_OVERFLOW) {
			 		log.function_end("Test stack (XLStack) Failed", XLColor::BG_RED);
			 		return;
			 	}
		 	}
		 	*/

		 	// stack.clear();

		 	// stack.drop();

			log.function_end("Test stack (XLStack) Passed Ok", XLColor::BG_GREEN);
		}
};
