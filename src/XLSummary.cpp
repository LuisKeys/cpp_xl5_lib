#include <iostream>
#include <limits>
#include <omp.h>
#include "XLSummary.h"
#include "XLLog.h"

float XLSummary::max(float * input, int len) {	
	XLLog log;
	log.function_start("XLSummary::max");
  
  max_result = std::numeric_limits<int>::min();

  omp_set_num_threads(6);
  #pragma omp parallel for reduction(max: max_result)
  for(int i = 0; i < len; ++i) {
    if(max_result < input[i])
      max_result = input [i]; 
  }

	log.function_end("XLSummary::max");
  return max_result;
}

float XLSummary::sum(float * input, int len) {	
	XLLog log;
	log.function_start("XLSummary::sum");
  
  sum_result = 0;
  
  for(int i = 0; i < len; ++i) {
    sum_result += input[i]; 
  }

	log.function_end("XLSummary::sum");
  return sum_result;
}