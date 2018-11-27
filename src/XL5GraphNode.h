#pragma once

#include <iostream>
#include "XL5Log.h"

class XL5GraphNode {
public:
  XL5GraphNode(int node_id) {
    _node_id = node_id;
  }

  void set_id(int node_id) {
    _node_id = node_id;
  }

  int get_id() {
    return _node_id;
  }

private:
  int _node_id = 0;
};
