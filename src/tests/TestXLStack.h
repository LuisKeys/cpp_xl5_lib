#pragma once

#include <iostream>
#include "../XLLog.h"
#include "../XLStack.h"

class TestXLStack {
	public:
		void test(int verbose) {
		 	XLLog log;
		 	XLStack<float> stack;
			int len = 4;
		 	float* popped_numbers = new float(len);
		 	float* numbers = new float(len);

		 	numbers[0] = 10;
		 	numbers[1] = 20;
		 	numbers[2] = 36;
		 	numbers[3] = 48;

		 	stack.create(1000);

		 	for(int i = 0; i < len; ++i) {
			 	int status = stack.push(numbers[i]);
				if(status == XL_STACK_ERR_STACK_OVERFLOW)
					log.text("Stack overflow", XLColor::FG_RED);
		 	}

			if(verbose) {
				stack.print();

				log.separator(XLColor::FG_GREEN);

				log.value("Get from position 1", stack.get(1), XLColor::FG_GREEN);
				stack.print();

				log.separator(XLColor::FG_GREEN);

				stack.set(1, 100);
				stack.print();

				log.separator(XLColor::FG_GREEN);

				stack.insert(1, 80);
				stack.print();

				log.separator(XLColor::FG_GREEN);

				log.value("Pop from position 1", stack.pop(1), XLColor::FG_GREEN);
				stack.print();

				log.separator(XLColor::FG_GREEN);
			}

		 	for(int i = 0; i < len; ++i) {
				popped_numbers[i] = stack.pop();
		 	}

			if(verbose)
				log.array("popped numbers", popped_numbers, len, XLColor::FG_YELLOW);
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
