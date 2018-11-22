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

  TestXLStack testXLStack;
  testXLStack.test(verbose);

  TestXLGraph testXLGraph;
  testXLGraph.test(verbose);

/*
  TestXLStack testXLStack;
  TestXLSort testXLSort;
  TestXLSummary testXLSummary;
  TestXLQueue testXLQueue;
  TestXLBinaryTree testXLBinaryTree;

  testXLSort.test(verbose);
  testXLSummary.test(verbose);
  testXLQueue.test(verbose);
  testXLBinaryTree.test(verbose);
  testXLStack.test(verbose);
  */
}
