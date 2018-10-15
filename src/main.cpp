#include <iostream>
#include "XLLog.h"
#include "XLSummary.h"

#define N1 100000

int main(int argc, char** argv)
{

  XLSummary summary;  

  int* numbers = new int[N1];

  for(int i = 0; i < N1; ++i) {
    numbers[i] = i;
  }

  int result = summary.xlmax(numbers, N1);
  delete numbers;

  std::cout << "Result:" << std::endl;
  std::cout << result << std::endl;
  return 0;
}
