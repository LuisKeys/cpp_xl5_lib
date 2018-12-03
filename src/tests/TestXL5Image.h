#pragma once

#include <iostream>
#include "../XL5Log.h"
#include "../XL5Image.h"

class TestXL5Image {
  public:
    void test(int verbose) {
      XL5Log log;
      XL5Image image;

      // Create a sample graph
      log.text("Test Image> Load PGM", XL5Color::FG_DEFAULT);
      string base_path = "./data/att_faces/s1/";
      int type = image.load_pgm(base_path + string("1.pgm"));
      XL5Matrix<uint8_t>* image_data = image.get_pgm_gray_data();
      std::cout << image_data->rows_count() << std::endl;
    }
};
