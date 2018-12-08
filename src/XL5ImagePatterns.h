#pragma once

#include <iostream>
#include <limits>
#include "XL5File.h"
#include "XL5Image.h"
#include "XL5Matrix.h"
#include "XL5Stack.h"
using namespace std;

class XL5ImagePatterns {
  public:
    void load_paterns(const string& patterns_path) {
      XL5File file;
      _patterns_buffer = new XL5Stack<XL5Matrix<uint8_t>*>();
      _patterns_buffer->create(1000, 100);
      XL5Stack<string>* files = file.list_dir(patterns_path);
      for(int i = 0; i < files->size(); ++i) {
        XL5Image* pattern = new XL5Image();
        string full_path = patterns_path + files->get(i);
        pattern->load_pgm(full_path);
        XL5Matrix<uint8_t>* pattern_data = pattern->get_gray_channel_data();
        _patterns_buffer->push(pattern_data);
      }
      // _patterns_buffer->log("Patterns pointers:", XL5Color::FG_GREEN);
      files->drop();
      delete files;
    }

    void drop_patterns() {
      _patterns_buffer->drop();
      delete _patterns_buffer;
    }

  private:
    XL5Stack<XL5Matrix<uint8_t>*>* _patterns_buffer;
};
