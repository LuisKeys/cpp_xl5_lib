#include <iostream>
#include <exception>
#include "TestXLSummary.h"
#include "../XLLog.h"
#include "../XLSummary.h"

void TestXLSummary::test(int verbose)
{
 	XLLog log;
 	XLSummary summary;

	int num_elements = 1000;
	float* numbers = new float[num_elements];

	for(int i = num_elements; i >= 0; --i) numbers[num_elements - i - 1] = i;

	if(verbose)
		log.array("Array to find max", numbers, num_elements, XLColor::FG_DEFAULT);

	float max = summary.max(numbers, num_elements);

	if(verbose)
		log.value("number of elements:", num_elements, XLColor::FG_DEFAULT);

	if(verbose)
		log.value("Max value:", max, XLColor::FG_DEFAULT);

	if(max != num_elements - 1){
		log.function_end("Test Max (XLSummary) Failed!", XLColor::BG_RED);
		return;
	}

	log.function_end("Test Max (XLSummary) Passed Ok", XLColor::BG_GREEN);

	if(verbose)
		log.array("Array to find min", numbers, num_elements, XLColor::FG_DEFAULT);

	float min = summary.min(numbers, num_elements);

	if(verbose)
		log.value("number of elements:", num_elements, XLColor::FG_DEFAULT);

	if(verbose)
		log.value("Min value:", min, XLColor::FG_DEFAULT);

	if(min != 0){
		log.function_end("Test Min (XLSummary) Failed!", XLColor::BG_RED);
		return;
	}

	log.function_end("Test min (XLSummary) Passed Ok", XLColor::BG_GREEN);

}


