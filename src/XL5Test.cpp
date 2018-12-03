#include <iostream>
#include "XL5Test.h"
#include "XL5Log.h"
#include "tests/TestXL5BinaryTree.h"
#include "tests/TestXL5Graph.h"
#include "tests/TestXL5Image.h"
#include "tests/TestXL5Matrix.h"
#include "tests/TestXL5Sort.h"
#include "tests/TestXL5Stack.h"
#include "tests/TestXL5Summary.h"
#include "tests/TestXL5Queue.h"

// Description: Main unit tests entry point class
// verbose > 1 to turn on verbose mode
void XL5Test::test(int verbose) {

  xl5_clear_console();

  TestXL5Image testXL5Image;
  testXL5Image.test(verbose);

/*
  TestXL5BinaryTree testXL5BinaryTree;
  TestXL5Graph testXL5Graph;
  TestXL5Image testXL5Image;
  TestXL5Matrix testXL5Matrix;
  testXL5Matrix.test(verbose);
  TestXL5Sort testXL5Sort;
  TestXL5Stack testXL5Stack;
  TestXL5Summary testXL5Summary;
  TestXL5Queue testXL5Queue;

  testXL5BinaryTree.test(verbose);
  testXL5Graph.test(verbose);
  testXL5Image.test(verbose);
  testXL5Sort.test(verbose);
  testXL5Stack.test(verbose);
  testXL5Summary.test(verbose);
  testXL5Queue.test(verbose);
*/
}
