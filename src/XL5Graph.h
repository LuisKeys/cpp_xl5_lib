#pragma once

#include <iostream>
#include "XL5Stack.h"
#include "XL5Log.h"
#include "XL5GraphNode.h"
#include "XL5Memory.h"

// Graph object and its related operations
class XL5Graph {
  public:
    // Initialize graph object
    void create(int max_nodes_num, int grow_size) {
      XL5Memory::new_object();
      _root_stack = new XL5Stack<XL5Stack<XL5GraphNode*>*>();
      _root_stack->create(max_nodes_num, grow_size);
      _max_nodes_num = max_nodes_num;
      _grow_size = grow_size;
    }

    // Add base node
    void add_base_node(XL5GraphNode* node) {
      XL5Memory::new_object();
      XL5Stack<XL5GraphNode*>* node_root_stack = new XL5Stack<XL5GraphNode*>();
      node_root_stack->create(_max_nodes_num, _grow_size);
      node_root_stack->push(node);
      _root_stack->push(node_root_stack);
    }

    // Add linked node
    void add_linked_node(XL5GraphNode* base_node, XL5GraphNode* linked_node) {
      // search base node
      int n = _root_stack->size();
      for(int i = 0; i < n; ++i) {
        XL5Stack<XL5GraphNode*>* child_root_stack = _root_stack->get(i);
        XL5GraphNode* iter_base_node = child_root_stack->get(0);
        if(iter_base_node->get_node_id() == base_node->get_node_id()) {
          XL5Memory::delete_object();
          child_root_stack->push(linked_node);
        }
      }
    }

    // drop all nodes from memory
    void drop() {
      int n = _root_stack->size();

      for(int i = 0; i < n; ++i) {
        XL5Stack<XL5GraphNode*>* child_root_stack = _root_stack->get(i);
        child_root_stack->clear();
        XL5Memory::delete_object();
        delete child_root_stack;
      }

      XL5Memory::delete_object();
      delete _root_stack;
    }

    // drop all nodes from memory
    void log(int is_directed) {
      int n = _root_stack->size();

      for(int i = 0; i < n; ++i) {
        XL5Stack<XL5GraphNode*>* child_root_stack = _root_stack->get(i);
        XL5GraphNode* base_node = child_root_stack->get(0);
        base_node->log_base_node();

        int sub_n = child_root_stack->size();

        for(int j = 1; j < sub_n; ++j) {
          XL5GraphNode* linked_node = child_root_stack->get(j);
          if(is_directed == 0)
            cout << '<'<< '-'<< '>';
          else
            cout << '-'<< '-'<< '>';

          linked_node->log_linked_node();
        }

        cout << '\n';
        cout << '\n';
      }

      cout << '\n';
      cout << '\n';
    }

  private:
    //Stack to hold the list
    XL5Stack<XL5Stack<XL5GraphNode*>*>* _root_stack;
    int _max_nodes_num = 0;
    int _grow_size = 0;
};
