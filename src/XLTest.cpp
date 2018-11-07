#include <iostream>
#include "XLTest.h"
#include "XLLog.h"
#include "tests/TestXLSort.h"
#include "tests/TestXLSummary.h"
#include "tests/TestXLStack.h"
#include "tests/TestXLQueue.h"
#include "tests/TestXLBinaryTree.h"
#include "tests/TestXLGraph.h"

// Description: Main unit tests entry point class
// verbose > 1 to turn on verbose mode
void XLTest::test(int verbose) {

  TestXLSort testXLSort;
  TestXLSummary testXLSummary;
  TestXLStack testXLStack;
  TestXLQueue testXLQueue;
  TestXLBinaryTree testXLBinaryTree;
  TestXLGraph testXLGraph;

  testXLSort.test(verbose);
  testXLSummary.test(verbose);
  testXLStack.test(verbose);
  testXLQueue.test(verbose);
  testXLBinaryTree.test(verbose);
  testXLGraph.test(verbose);
}
