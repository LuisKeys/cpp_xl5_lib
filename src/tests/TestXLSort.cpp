#include <iostream>
#include "TestXLSort.h"
#include "../XLLog.h"
#include "../XLSort.h"

void TestXLSort::test(int verbose)
{
 	XLLog log;
 	XLSort sort;

	int num_elements = 1000;
	float* numbers = new float[num_elements];

	for(int i = num_elements; i >= 0; --i) numbers[num_elements - i - 1] = i;

	if(verbose)
		log.array("Array to sort", numbers, num_elements, XLColor::FG_DEFAULT);

	sort.sort(numbers, num_elements);

	if(verbose)
		log.value("number of elements:", num_elements, XLColor::FG_DEFAULT);

	if(verbose)
		log.array("Sorted", numbers, num_elements, XLColor::FG_DEFAULT);

	 
	log.function_end("Test Merge Sort (XLSort) Passed Ok", XLColor::BG_GREEN);
}


