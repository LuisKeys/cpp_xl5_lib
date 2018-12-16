#pragma once

#include <iostream>
#include <limits>
#include "XL5File.h"
#include "XL5Image.h"
#include "XL5Log.h"
#include "XL5MLLogisticRegression.h"
#include "XL5Matrix.h"
#include "XL5Stack.h"
using namespace std;

class XL5ImagePattern {
  public:
    void load_patterns(const string& patterns_path) {
      XL5File file;
      string negative_prefix = "no_";

      XL5Memory::new_object();
      _patterns_buffer = new XL5Stack<XL5Matrix<float>*>();

      XL5Memory::new_object();
      _targets = new XL5Stack<int>();

      _patterns_buffer->create(100, 100);
      _targets->create(100, 100);

      XL5Stack<string>* files = file.list_dir(patterns_path);
      for(int i = 0; i < files->size(); ++i) {
        // create image matrix and load
        XL5Memory::new_object();
        XL5Image* pattern = new XL5Image();
        string full_path = patterns_path + files->get(i);

        pattern->load_pgm(full_path);

        // get gray channel  data
        XL5Matrix<uint8_t>* pattern_data = pattern->get_gray_channel_data();

        // clone to float
        XL5Matrix<float>* pattern_data_float = pattern_data->clone_to_float();

        // change from rectangle to horizontal matrix layout
        XL5Matrix<float>* pattern_data_float_lh = pattern_data_float->linear_horizontal();

        // normalize to [-1.0; 1.0]
        pattern_data_float_lh->normalize(-1.0, 1.0, 0.0, 255.0);
        // pattern_data_float_lh->log("pattern_data:", XL5Color::FG_YELLOW, 2);

        // add feature to stack
        _patterns_buffer->push(pattern_data_float_lh);
        // add target to stack
        if(files->get(i).compare(0, negative_prefix.size(), negative_prefix) == 0) {
          _targets->push(0);
        }
        else {
          _targets->push(1);
        }

        pattern_data_float->drop();
        XL5Memory::delete_object();
        delete pattern_data_float;

        pattern->drop_pgm_gray();
        XL5Memory::delete_object();
        delete pattern;
      }

      // _patterns_buffer->log("Patterns pointers:", XL5Color::FG_GREEN);
      files->drop_delete();
      XL5Memory::delete_object();
      delete files;
    }

    XL5MLLogisticRegression<float>* train_logistic_regression() {
      XL5Log log;
      XL5Memory::new_object();
      _lr = new XL5MLLogisticRegression<float>();
      _lr->create(_patterns_buffer->get(0)->cols_count());

      int counter = 0;
      std::cout << "Start training ----------------------------" << '\n';
      for(int iteration = 0; iteration < 1000; ++iteration) {
        for(int i = 0; i < _patterns_buffer->size(); ++i) {
          XL5Matrix<float>* X = _patterns_buffer->get(i);
          counter++;
          _lr->train(X, _targets->get(i), 0.001);
          if(counter % 1000 == 0) {
            std::cout << "Prediction:" << _lr->get_estimation() << '\n';
            std::cout << "Target:" << _targets->get(i) << '\n';
          }
        }
      }
      std::cout << "End training ----------------------------" << '\n' << '\n';

      std::cout << "Start testing ----------------------------" << '\n';
      for(int i = 0; i < _patterns_buffer->size(); ++i) {
        XL5Matrix<float>* X = _patterns_buffer->get(i);
        // X->log("X:", XL5Color::FG_YELLOW, 4);
        _lr->predict(X);
        int color = XL5Color::FG_GREEN;

        if(_targets->get(i) != (int)_lr->get_estimation()) {
          color = XL5Color::FG_RED;
        }
        log.value_line("Prediction", _lr->get_estimation(), color);
        log.value_line(" - Non rounded prediction", _lr->get_non_rounded_estimation(), color);
        log.value(" - Target", _targets->get(i), color);
      }
      std::cout << "End testing ----------------------------" << '\n' << '\n';

      return _lr;
    }

    void drop() {
      for(int i = 0; i < _patterns_buffer->size(); ++i) {
         XL5Matrix<float>* pattern_data = _patterns_buffer->get(i);
         pattern_data->drop();
         XL5Memory::delete_object();
         delete pattern_data;
      }

      _patterns_buffer->drop();
      XL5Memory::delete_object();
      XL5Memory::delete_object();
      delete _patterns_buffer;

      _targets->drop();
      XL5Memory::delete_object();
      delete _targets;

    }

  private:
    XL5MLLogisticRegression<float>* _lr;
    XL5Stack<XL5Matrix<float>*>* _patterns_buffer;
    XL5Stack<int>* _targets;
};
