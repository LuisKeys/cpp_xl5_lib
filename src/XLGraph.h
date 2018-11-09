#pragma once

#include <iostream>
#include "XLStack.h"
#include "XLLog.h"
#include "XLGraphNode.h"

// Graph object and its related operations
class XLGraph {
  public:
    // Initialize graph object
    void create(int max_nodes_num) {
      _stack.create(max_nodes_num);
    }

    // Add node
    void add(XLGraphNode* node) {
      XLStack<XLGraphNode*>* node_stack = new XLStack<XLGraphNode*>();
      node_stack->push(node);
      _stack.push(node_stack);
    }

  private:
    //Stack to hold the list
    XLStack<XLStack<XLGraphNode*>*> _stack;
};
