#pragma once

#include <iostream>
#include "../XL5Log.h"
#include "../XL5Stack.h"

class TestXL5Stack {
	public:
		void test(int verbose) {
		 	XL5Log log;
		 	XL5Stack<float> stack;
			int len = 4;
			XL5Memory::new_object();
		 	float* popped_numbers = new float(len);
			XL5Memory::new_object();
		 	float* numbers = new float(len);

		 	numbers[0] = 10;
		 	numbers[1] = 20;
		 	numbers[2] = 36;
		 	numbers[3] = 48;

		 	stack.create(1000, 100);

		 	for(int i = 0; i < len; ++i) {
			 	int status = stack.push(numbers[i]);
				if(status == XL5_STACK_ERR_STACK_OVERFLOW)
					log.text("Stack overflow", XL5Color::FG_RED);
		 	}

			if(verbose) {
				stack.print();

				log.separator(XL5Color::FG_GREEN);

				log.value("Get from position 1", stack.get(1), XL5Color::FG_GREEN);
				stack.print();

				log.separator(XL5Color::FG_GREEN);

				stack.set(1, 100);
				stack.print();

				log.separator(XL5Color::FG_GREEN);

				stack.insert(1, 80);
				stack.print();

				log.separator(XL5Color::FG_GREEN);

				log.value("Pop from position 1", stack.pop(1), XL5Color::FG_GREEN);
				stack.print();

				log.separator(XL5Color::FG_GREEN);
			}

		 	for(int i = 0; i < len; ++i) {
				popped_numbers[i] = stack.pop();
		 	}

			if(verbose)
				log.array<float>("popped numbers", popped_numbers, len, XL5Color::FG_YELLOW);
		 	/*
		 	for(int i = 0; i < 11; ++i) {
			 	int status = stack.push(numbers);
			 	if(status == XL5_STACK_ERR_STACK_OVERFLOW) {
			 		log.function_end("Test stack (XL5Stack) Failed", XL5Color::BG_RED);
			 		return;
			 	}
		 	}
		 	*/

		 	stack.clear();

		 	stack.drop();

			log.function_end("Test stack (XL5Stack) Passed Ok", XL5Color::BG_GREEN);
		}
};
