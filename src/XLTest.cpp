#include <iostream>
#include "XLTest.h"
#include "XLLog.h"
#include "tests/TestXLSort.h"
#include "tests/TestXLSummary.h"
#include "tests/TestXLStack.h"
#include "tests/TestXLQueue.h"

void XLTest::test(int verbose) {	

  TestXLSort testXLSort;
  TestXLSummary testXLSummary;
  TestXLStack testXLStack;
  TestXLQueue testXLQueue;

  testXLSort.test(verbose);
  testXLSummary.test(verbose);
  testXLStack.test(verbose);
  testXLQueue.test(verbose);
  
}