#include <iostream>
#include "XLTest.h"
#include "XLLog.h"
#include "tests/TestXLSort.h"

void XLTest::test(int verbose) {	

  TestXLSort testXLSort;
  testXLSort.test(verbose);
}