#pragma once

#include <iostream>
#include "../XL5Log.h"
#include "../XL5Graph.h"

class TestXL5Graph {
  public:
    void test(int verbose) {
      XL5Log log;
      XL5Graph graph;

      // Create a sample graph
      graph.create(1000);
    }
};
