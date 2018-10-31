#include <iostream>
#include <exception>
#include "TestXLQueue.h"
#include "../XLLog.h"
#include "../XLQueue.h"

void TestXLQueue::test(int verbose)
{
 	XLLog xlLog;
 	XLQueue<float> stack;
 	float* dequeued_numbers = new float[4];

 	stack.create(10);

 	
 	for(int i = 1; i < 5; ++i) {
	 	if(verbose) xlLog.value("Enqueued value", i, XLColor::FG_YELLOW);
	 	stack.enqueue((float)i);
 	}

 	for(int i = 0; i < 5; ++i) {
	 	float a = stack.dequeue();	 	
	 	xlLog.value("Dequed value", a, XLColor::FG_YELLOW);
	 	dequeued_numbers[i] = a;
 	}
 	
 	stack.clear();

 	stack.drop();

 	for(int i = 0; i < 4; ++i) {
 		float a = (float)(i + 1);
 		float b = dequeued_numbers[i]; 			
 		if(verbose) xlLog.value("a value", a, XLColor::FG_YELLOW);
 		if(verbose) xlLog.value("b value", b, XLColor::FG_YELLOW);
 		if(a != b) {
			xlLog.function_end("Test stack (XLQueue) Failed", XLColor::BG_RED);
 			return;
 		}
 	}

	xlLog.function_end("Test stack (XLQueue) Passed Ok", XLColor::BG_GREEN);
}
