#pragma once

#include <iostream>
#include "XL5Log.h"

class XL5GraphNode {
public:
  XL5GraphNode(int node_id) {
    _node_id = node_id;
  }

  XL5GraphNode(int node_id, int layer_id) {
    _node_id = node_id;
    _layer_id = layer_id;
  }

  void set_node_id(int node_id) {
    _node_id = node_id;
  }

  int get_node_id() {
    return _node_id;
  }

  void set_layer_id(int node_id) {
    _node_id = node_id;
  }

  int get_layer_id() {
    return _node_id;
  }

  // log base node
  void log_base_node() {
    cout << "\033[" << XL5Color::BG_BLUE << "m" << " " << _node_id<< " " << "\033[0m";
  }

  // log linked node
  void log_linked_node() {
    cout << "\033[" << XL5Color::BG_GREEN << "m" << " " << _node_id<< " " << "\033[0m";
  }

private:
  int _node_id = 0;
  int _layer_id = 0;
};
