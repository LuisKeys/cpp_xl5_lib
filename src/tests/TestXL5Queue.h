#pragma once

#include <iostream>
#include "../XL5Log.h"
#include "../XL5Queue.h"

class TestXL5Queue {
	public:
		void test(int verbose) {
		 	XL5Log XL5Log;
		 	XL5Queue<float> stack;
		 	float* dequeued_numbers = new float[4];

		 	stack.create(10);


		 	for(int i = 1; i < 5; ++i) {
			 	if(verbose) XL5Log.value("Enqueued value", i, XL5Color::FG_YELLOW);
			 	stack.enqueue((float)i);
		 	}

		 	for(int i = 0; i < 5; ++i) {
			 	float a = stack.dequeue();
			 	if(verbose) XL5Log.value("Dequed value", a, XL5Color::FG_YELLOW);
			 	dequeued_numbers[i] = a;
		 	}

		 	stack.clear();

		 	stack.drop();

		 	for(int i = 0; i < 4; ++i) {
		 		float a = (float)(i + 1);
		 		float b = dequeued_numbers[i];
		 		if(verbose) XL5Log.value("a value", a, XL5Color::FG_YELLOW);
		 		if(verbose) XL5Log.value("b value", b, XL5Color::FG_YELLOW);
		 		if(a != b) {
					XL5Log.function_end("Test stack (XL5Queue) Failed", XL5Color::BG_RED);
		 			return;
		 		}
		 	}

			XL5Log.function_end("Test stack (XL5Queue) Passed Ok", XL5Color::BG_GREEN);
		}
};
