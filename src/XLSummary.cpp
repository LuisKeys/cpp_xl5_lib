#include <iostream>
#include <limits>
#include "XLSummary.h"
#include "XLLog.h"

int XLSummary::max(int * input, int len) {	
	XLLog log;
	log.function_start("XLSummary::max");
  int max = std::numeric_limits<int>::min();
  for(int i = 0; i < len; ++i) {
    if(max < input[i])
      max = input [i]; 
  }

	log.function_end("XLSummary::max");
  return max;
}

int XLSummary::sum(int * input, int len) {	
	XLLog log;
	log.function_start("XLSummary::sum");
  int sum = 0;
  for(int i = 0; i < len; ++i) {
    sum += input[i]; 
  }

	log.function_end("XLSummary::sum");
  return sum;
}