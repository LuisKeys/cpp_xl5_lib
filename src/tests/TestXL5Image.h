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
      image.save_pgm_gray("proc_1.pgm", image_data, "XL5 Processed pgm image");
    }
};
