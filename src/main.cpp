#include <iostream>
#include <cmath>
#include "XLLog.h"
#include "XLSummary.h"

int main(int argc, char** argv)
{

  XLSummary summary;  

  int num_elements = pow(10, 6);

  int* numbers = new int[num_elements];

  for(int i = 0; i < num_elements; ++i) {
    numbers[i] = i;
  }

  int result = summary.sum(numbers, num_elements);
  delete numbers;

  std::cout << "Result:" << std::endl;
  std::cout << result << std::endl;
  return 0;
}

