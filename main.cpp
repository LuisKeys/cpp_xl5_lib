#include <iostream>
#include <cmath>
#include "src/XL5Test.h"
#include "src/XL5Memory.h"

int main(int argc, char** argv)
{
  XL5Test test;
  int verbose = true;

  // Executes unit tests
  test.test(verbose);

  XL5Memory::log();
  return 0;
}
