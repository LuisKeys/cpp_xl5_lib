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
      log.function_start("Test Graph > Create", XL5Color::FG_DEFAULT);

      graph.create(1000);

      XL5GraphNode* node = new XL5GraphNode(1);
      graph.add_base_node(node);

      
      graph.drop();

      log.function_end("test Graph > End", XL5Color::FG_DEFAULT);
    }
};
