#pragma once

#include <iostream>
#include "../XLLog.h"
#include "../XLGraph.h"

class TestXLGraph {
  public:
    void test(int verbose) {
      XLLog log;
      XLGraph graph;

      // Create a sample graph
      graph.create(1000);
    }
};
