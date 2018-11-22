#pragma once

#include <iostream>
#include "XL5Stack.h"
#include "XL5Log.h"
#include "XL5GraphNode.h"

// Graph object and its related operations
class XL5Graph {
  public:
    // Initialize graph object
    void create(int max_nodes_num) {
      _stack.create(max_nodes_num);
    }

    // Add node
    void add(XL5GraphNode* node) {
      XL5Stack<XL5GraphNode*>* node_stack = new XL5Stack<XL5GraphNode*>();
      node_stack->push(node);
      _stack.push(node_stack);
    }

  private:
    //Stack to hold the list
    XL5Stack<XL5Stack<XL5GraphNode*>*> _stack;
};
