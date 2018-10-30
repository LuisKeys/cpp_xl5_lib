#include <iostream>
#include <limits>
#include "XLSummary.h"
#include "XLLog.h"

float XLSummary::max(float * input, int len) {	
	XLLog log;
	log.function_start("XLSummary::max", XLColor::FG_DEFAULT);
  
  float max_result = std::numeric_limits<int>::min();

  for(int i = 0; i < len; ++i) {
    if(max_result < input[i])
      max_result = input [i]; 
  }

	log.function_end("XLSummary::max", XLColor::FG_DEFAULT);
  return max_result;
}

float XLSummary::min(float * input, int len) {  
  XLLog log;
  log.function_start("XLSummary::max", XLColor::FG_DEFAULT);
  
  float min_result = std::numeric_limits<int>::max();

  for(int i = 0; i < len; ++i) {
    if(min_result > input[i])
      min_result = input [i]; 
  }

  log.function_end("XLSummary::min", XLColor::FG_DEFAULT);
  return min_result;
}

float XLSummary::sum(float * input, int len) {	
	XLLog log;
	log.function_start("XLSummary::sum", XLColor::FG_DEFAULT);
  
  sum_result = 0;
  
  for(int i = 0; i < len; ++i) {
    sum_result += input[i]; 
  }

	log.function_end("XLSummary::sum", XLColor::FG_BLUE);
  return sum_result;
}