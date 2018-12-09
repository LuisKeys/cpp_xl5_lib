#pragma once

#include <iostream>
#include "XL5Log.h"

template <class T>
class XL5Memory {
  public:
    static XL5Stack<string>* _stack;

    static T* new_object(string description) {
        _add_element();

      return new T();
    }

    static T* new_array (int size, string description) {
      _add_element();

      return new T[size];
    }

    static void delete_object(T* object, string description) {
      _remove_element(description);
      delete object;
    }

    static void log() {
      _stack->log("Remaining heap memory elements", XL5Color::FG_RED);
    }

  private:
    void _add_element(string description) {
      if(_stack == NULL) {
        _stack = new XL5Stack<string>();
        _stack->create(1000, 100);
      }

      _stack->push(description);
    }

    void _remove_element(string description) {
      if(_stack == NULL) {
        return;
      }

      for(int i = 0; i < _stack->size(); ++i) {
        if(_stack->get(i) == description) {
          _stack->pop(i);
        }
      }
    }
};
