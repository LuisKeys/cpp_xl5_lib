#include <iostream>
#include <limits>
#include "XLSummary.h"

int XLSummary::xlmax(int * input, int len) {	
	std::cout << "XL_Summary" << std::endl;
  int max = std::numeric_limits<int>::min();
  for(int i = 0; i < len; ++i) {
    if(max < input[i])
      max = input [i]; 
  }

  return max;
}