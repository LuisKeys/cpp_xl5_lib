#include <iostream>
#include <cmath>
#include "src/XLTest.h"

int main(int argc, char** argv)
{
  XLTest test;
  int verbose = true;

  // Executes unit tests
  test.test(verbose);

  return 0;
}
