#include <iostream>
#include <exception>
#include "TestXLSummary.h"
#include "../XLLog.h"
#include "../XLSummary.h"

void TestXLSummary::test(int verbose)
{
 	XLLog log;
 	XLSummary summary;
	try {

		int num_elements = 100000000;
		float* numbers = new float[num_elements];

		for(int i = num_elements; i >= 0; --i) numbers[num_elements - i - 1] = i;

		if(verbose)
			log.array("Array to find max", numbers, num_elements, XLColor::FG_DEFAULT);

		float max = summary.max(numbers, num_elements);

		if(verbose)
			log.value("number of elements:", num_elements, XLColor::FG_DEFAULT);

		if(verbose)
			log.value("Max value:", max, XLColor::FG_DEFAULT);

		log.function_end("Test Max (XLSummary) Passed Ok", XLColor::BG_GREEN);
	}
	catch(int e) {
		log.function_end("Test Max (XLSummary) Failed!", XLColor::BG_RED);
	}
}


