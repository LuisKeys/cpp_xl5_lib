#include <iostream>
#include <limits>
#include "XLSummary.h"
#include "XLLog.h"

int XLSummary::max(int * input, int len) {	
	XLLog log;
	log.function_start("XL_Summary");
  int max = std::numeric_limits<int>::min();
  for(int i = 0; i < len; ++i) {
    if(max < input[i])
      max = input [i]; 
  }

	log.function_end("XL_Summary");
  return max;
}

int XLSummary::sum(int * input, int len) {	
	XLLog log;
	log.function_start("XL_Summary");
  int sum = 0;
  for(int i = 0; i < len; ++i) {
    sum += input[i]; 
  }

	log.function_end("XL_Summary");
  return sum;
}