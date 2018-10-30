#include <iostream>
#include "XLTest.h"
#include "XLLog.h"
#include "tests/TestXLSort.h"
#include "tests/TestXLSummary.h"
#include "tests/TestXLStack.h"

void XLTest::test(int verbose) {	

  TestXLSort testXLSort;
  TestXLSummary testXLSummary;
  TestXLStack testXLStack;

  testXLSort.test(verbose);
  testXLSummary.test(verbose);
  testXLStack.test(verbose);
}