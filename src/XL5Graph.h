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
      _root_stack = new XL5Stack<XL5Stack<XL5GraphNode*>*>();
      _root_stack->create(max_nodes_num);
      _max_nodes_num = max_nodes_num;
    }

    // Add base node
    void add_base_node(XL5GraphNode* node) {
      XL5Stack<XL5GraphNode*>* node_root_stack = new XL5Stack<XL5GraphNode*>();
      node_root_stack->create(_max_nodes_num);
      node_root_stack->push(node);
      _root_stack->push(node_root_stack);
    }

    // Add node
    void add_sub_node(int base_node_id, XL5GraphNode* node) {
      XL5Stack<XL5GraphNode*>* node_root_stack = new XL5Stack<XL5GraphNode*>();
      node_root_stack->create(_max_nodes_num);
      node_root_stack->push(node);
      _root_stack->push(node_root_stack);
    }

    // drop all nodes from memory
    void drop() {
      int n = _root_stack->size();

      for(int i = 0; i < n; ++i) {
        XL5Stack<XL5GraphNode*>* child_root_stack = _root_stack->get(i);
        std::cout << child_root_stack->size() << '\n';
        child_root_stack->clear();
        delete child_root_stack;
      }

      delete _root_stack;
    }

  private:
    //Stack to hold the list
    XL5Stack<XL5Stack<XL5GraphNode*>*>* _root_stack;
    int _max_nodes_num = 0;
};
