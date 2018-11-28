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

      graph.create(1000, 100);

      XL5GraphNode* node_1 = new XL5GraphNode(1, 0);
      graph.add_base_node(node_1);
      XL5GraphNode* node_2 = new XL5GraphNode(2, 1);
      graph.add_base_node(node_2);
      XL5GraphNode* node_3 = new XL5GraphNode(5, 0);
      graph.add_base_node(node_3);
      XL5GraphNode* node_4 = new XL5GraphNode(4, 1);
      graph.add_base_node(node_4);
      XL5GraphNode* node_5 = new XL5GraphNode(3, 2);
      graph.add_base_node(node_5);

      graph.add_linked_node(node_1, node_2);
      graph.add_linked_node(node_1, node_5);

      graph.add_linked_node(node_2, node_1);
      graph.add_linked_node(node_2, node_5);
      graph.add_linked_node(node_2, node_3);
      graph.add_linked_node(node_2, node_4);

      graph.log(1);

      graph.drop();

      log.function_end("test Graph > End", XL5Color::FG_DEFAULT);
    }
};
