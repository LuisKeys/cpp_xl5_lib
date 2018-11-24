#include <iostream>
#include "XL5Test.h"
#include "XL5Log.h"
#include "tests/TestXL5Sort.h"
#include "tests/TestXL5Summary.h"
#include "tests/TestXL5Stack.h"
#include "tests/TestXL5Queue.h"
#include "tests/TestXL5BinaryTree.h"
#include "tests/TestXL5Graph.h"
#include "tests/TestXL5Matrix.h"

// Description: Main unit tests entry point class
// verbose > 1 to turn on verbose mode
void XL5Test::test(int verbose) {

  xl5_clear_console();

  TestXL5Matrix testXL5Matrix;
  testXL5Matrix.test(verbose);

/*
  TestXL5Graph testXL5Graph;
  testXL5Graph.test(verbose);

  TestXL5Stack testXL5Stack;
  TestXL5Sort testXL5Sort;
  TestXL5Summary testXL5Summary;
  TestXL5Queue testXL5Queue;
  TestXL5BinaryTree testXL5BinaryTree;

  testXL5Sort.test(verbose);
  testXL5Summary.test(verbose);
  testXL5Queue.test(verbose);
  testXL5BinaryTree.test(verbose);
  testXL5Stack.test(verbose);
  */
}
