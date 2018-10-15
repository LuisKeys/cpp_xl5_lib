#include <iostream>
#include <cmath>
#include "XLLog.h"
#include "XLSort.h"
#include "XLSummary.h"

int main(int argc, char** argv)
{
  XLSummary summary;
  XLSort sort;
  XLLog log;

  int num_elements = pow(10, 1);

  float* numbers = new float[num_elements];

  for(int i = num_elements - 1; i >= 0; --i) {
    numbers[num_elements - i - 1] = (float)i;
  }

  log.array("numbers", numbers, num_elements);

  sort.sort(numbers, num_elements);

  log.array("numbers", numbers, num_elements);

  delete numbers;

  std::cout << "Result:" << std::endl;
  return 0;
}


