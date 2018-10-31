#include <iostream>
#include <exception>
#include "TestXLStack.h"
#include "../XLLog.h"
#include "../XLStack.h"

void TestXLStack::test(int verbose)
{
 	XLLog log;
 	XLStack<float*> stack;
 	float* popped_numbers;

 	float* numbers = new float(4);
 	numbers[0] = 10;
 	numbers[1] = 20;
 	numbers[2] = 36;
 	numbers[3] = 48;

 	stack.create(10);

 	for(int i = 0; i < 10; ++i) {
	 	stack.push(numbers);
 	}

 	for(int i = 0; i < 10; ++i) {
	 	popped_numbers = stack.pop();
 	}
 	
 	/*
 	for(int i = 0; i < 11; ++i) {
	 	int status = stack.push(numbers);
	 	if(status == XL_STACK_ERR_STACK_OVERFLOW) {
	 		log.function_end("Test stack (XLStack) Failed", XLColor::BG_RED);
	 		return;
	 	}
 	}
 	*/

 	stack.clear();

 	stack.drop();

 	for(int i = 0; i < 4; ++i) {
 		if(numbers[i] != popped_numbers[i]) {
			log.function_end("Test stack (XLStack) Failed", XLColor::BG_RED);
 			return;
 		}
 	}

	log.function_end("Test stack (XLStack) Passed Ok", XLColor::BG_GREEN);
}
