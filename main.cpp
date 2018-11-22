#include <iostream>
#include <cmath>
#include "src/XL5Test.h"

int main(int argc, char** argv)
{
  XL5Test test;
  int verbose = true;

  // Executes unit tests
  test.test(verbose);

  return 0;
}
