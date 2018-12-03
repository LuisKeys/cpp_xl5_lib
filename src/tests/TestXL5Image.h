#pragma once

#include <iostream>
#include "../XL5Log.h"
#include "../XL5Image.h"
#include "../XL5ImageFilters.h"

class TestXL5Image {
  public:
    void test(int verbose) {
      XL5Log log;
      XL5Image image;
      XL5ImageFilters image_filters;

      log.text("Test Image> Load PGM", XL5Color::FG_DEFAULT);
      string base_path = "./data/att_faces/s1/";
      int type = image.load_pgm(base_path + string("1.pgm"));
      XL5Matrix<uint8_t>* image_data = image.get_gray_channel_data();
      XL5Matrix<uint8_t>* horiz_gradients = image_filters.get_horizontal_gradient(image_data);
      image.save_pgm_gray("h_grads_1.pgm", horiz_gradients, "XL5 Horizontal gradients");
      XL5Matrix<uint8_t>* vertical_gradients = image_filters.get_vertical_gradient(image_data);
      image.save_pgm_gray("v_grads_1.pgm", vertical_gradients, "XL5 Vertical gradients");
    }
};
