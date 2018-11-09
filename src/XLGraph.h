#pragma once

#include <iostream>
#include "XLStack.h"
#include "XLLog.h"
#include "XLGraphNode.h"

// Graph object and its related operations
class XLGraph {
  public:
    // Initialize graph object
    void create() {
    }

  public:
    //Stack to hold the list 
    XLStack<XLStack<XLGraphNode*>*> _stack;
};
