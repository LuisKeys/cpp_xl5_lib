#include <iostream>
#include "XLTest.h"
#include "XLLog.h"
#include "tests/TestXLSort.h"
#include "tests/TestXLSummary.h"

void XLTest::test(int verbose) {	

  TestXLSort testXLSort;
  TestXLSummary testXLSummary;

  testXLSort.test(verbose);
  testXLSummary.test(verbose);
}