#pragma once

#include <iostream>
#include "XL5Log.h"

class XL5Memory {
  public:

    static int* get_count() {
      static int counter;
      return &counter;
    }

    static void new_object() {
      int* counter_p = get_count();
      *counter_p = *counter_p + 1;
    }

    static void delete_object() {
      int* counter_p = get_count();
      if(*counter_p > 0)
        *counter_p = *counter_p - 1;
    }

    static void log() {
      int* counter_p = get_count();
      cout <<"Remaining heap memory elements:" << *counter_p << endl;
    }
};
