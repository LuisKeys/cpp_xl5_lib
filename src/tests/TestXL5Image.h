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

      for(int i = 1; i < 41; ++i) {
        string image_index = to_string(i);
        string source_file = string("1.pgm");
        string dest_file = image_index + string(".pgm");
        string base_path = string("./data/att_faces/s") + image_index + string("/");

        int type = image.load_pgm(base_path + source_file);
        XL5Matrix<uint8_t>* image_data = image.get_gray_channel_data();

        // XL5Matrix<uint8_t>* threholded_image = image_filters.get_threhold(image_data, 100);
        // image.save_pgm_gray(string("threholded_") + dest_file, threholded_image, "XL5 threholded image");

        XL5Matrix<uint8_t>* gradients = image_filters.get_vertical_gradient(image_data);
        // image.save_pgm_gray(string("gradients_") + source_file, gradients, "XL5 threholded gradients");

        XL5Matrix<uint8_t>* gradients_all_black = image_filters.get_white_to_black(gradients);
        // image.save_pgm_gray(string("black_") + source_file, gradients_all_black, "XL5 gradients all black");

        XL5Matrix<uint8_t>* gradients_b_g = image_filters.get_gray_to_black(gradients_all_black);
        // image.save_pgm_gray(string("BW_") + dest_file, gradients_b_g, "XL5 gradients b w");

        XL5Matrix<uint8_t>* gradients_b_w = image_filters.get_gray_to_white(gradients_b_g);
        image.save_pgm_gray(string("BW_") + dest_file, gradients_b_w, "XL5 gradients b w");

        // delete threholded_image;
        delete image_data;
        delete gradients;
        delete gradients_all_black;
        delete gradients_b_w;
      }
    }
};
