#pragma once

#include <iostream>
#include <limits>
#include "XL5Matrix.h"

#define MAX_BW_IMAGE_VALUE 255
#define MID_BW_IMAGE_VALUE 128
#define MIN_BW_IMAGE_VALUE 0

using namespace std;
// Images object and its related basic operations
class XL5ImageFilters {
  public:
    XL5Matrix<uint8_t> * get_white_to_black(XL5Matrix<uint8_t> * image_data) {
      return _get_color_jump(image_data, 250, 1);
    }

    XL5Matrix<uint8_t> * get_gray_to_white(XL5Matrix<uint8_t> * image_data) {
      return _get_color_jump(image_data, 120, 1);
    }

    XL5Matrix<uint8_t> * get_gray_to_black(XL5Matrix<uint8_t> * image_data) {
      return _get_color_jump(image_data, 120, 0);
    }

    XL5Matrix<uint8_t> * get_threhold(XL5Matrix<uint8_t> * image_data, int threhold) {
      XL5Memory::new_object();
      XL5Matrix<uint8_t> * threholded_gradients = new XL5Matrix<uint8_t>();
      int rows_count = image_data->rows_count();
      int cols_count = image_data->cols_count();
      uint8_t value;
      threholded_gradients->create(rows_count, cols_count, 0);

      for(int row = 1; row < rows_count - 1; ++row) {
        for(int col = 1; col < cols_count - 1; ++col) {
          value = image_data->get(row, col - 1);

          if(value > threhold)
            value = MAX_BW_IMAGE_VALUE;
          else
            value = 0;
          threholded_gradients->set(row, col, value);
        }
      }

      return threholded_gradients;
    }

    XL5Matrix<uint8_t> * get_horizontal_gradient(XL5Matrix<uint8_t> * image_data) {
      XL5Memory::new_object();
      XL5Matrix<uint8_t> * horiz_gradients = new XL5Matrix<uint8_t>();
      int rows_count = image_data->rows_count();
      int cols_count = image_data->cols_count();
      uint8_t left_pixel = 0;
      uint8_t right_pixel = 0;
      uint8_t scaled_diff = 0;

      if(rows_count < 1 || cols_count < 3)
         return horiz_gradients;

      horiz_gradients->create(rows_count, cols_count, 0);

      for(int row = 1; row < rows_count - 1; ++row) {
        for(int col = 1; col < cols_count - 1; ++col) {
          left_pixel = image_data->get(row, col - 1);
          right_pixel = image_data->get(row, col + 1);
          scaled_diff = (uint8_t)((float)(left_pixel - right_pixel) / 2.0) + 128;
          horiz_gradients->set(row, col, scaled_diff);
        }
      }

      for(int row = 0; row < rows_count; ++row) {
        uint8_t value = horiz_gradients->get(row, 1);
        horiz_gradients->set(row, 0, value);
        value = horiz_gradients->get(row, cols_count - 2);
        horiz_gradients->set(row, cols_count - 1, value);
      }

      return horiz_gradients;
    }

    XL5Matrix<uint8_t> * get_vertical_gradient(XL5Matrix<uint8_t> * image_data) {
      XL5Memory::new_object();
      XL5Matrix<uint8_t> * vertical_gradients = new XL5Matrix<uint8_t>();
      int rows_count = image_data->rows_count();
      int cols_count = image_data->cols_count();
      uint8_t top_pixel = 0;
      uint8_t bottom_pixel = 0;
      uint8_t scaled_diff = 0;

      if(rows_count < 3 || cols_count < 1)
         return vertical_gradients;

      vertical_gradients->create(rows_count, cols_count, 0);

      for(int row = 1; row < rows_count - 1; ++row) {
        for(int col = 1; col < cols_count - 1; ++col) {
          top_pixel = image_data->get(row - 1, col);
          bottom_pixel = image_data->get(row + 1, col);
          scaled_diff = (uint8_t)((float)(top_pixel - bottom_pixel) / 2.0) + 128;
          vertical_gradients->set(row, col, scaled_diff);
        }
      }

      for(int col = 0; col < cols_count; ++col) {
        uint8_t value = vertical_gradients->get(1, col);
        vertical_gradients->set(0, col, value);
        value = vertical_gradients->get(rows_count - 2, col);
        vertical_gradients->set(rows_count - 1, col, value);
      }

      return vertical_gradients;
    }
  private:
    XL5Matrix<uint8_t> * _get_color_jump(XL5Matrix<uint8_t> * image_data, int threhold, int is_increase) {
      XL5Memory::new_object();
      XL5Matrix<uint8_t> * threholded_image = new XL5Matrix<uint8_t>();
      int rows_count = image_data->rows_count();
      int cols_count = image_data->cols_count();
      uint8_t value;
      threholded_image->create(rows_count, cols_count, 0);

      for(int row = 1; row < rows_count - 1; ++row) {
        for(int col = 1; col < cols_count - 1; ++col) {
          value = image_data->get(row, col - 1);
          if(is_increase == 1) {
            if(value > threhold)
              value = MAX_BW_IMAGE_VALUE;
          }
          else {
            if(value < threhold)
              value = 0;
          }
          threholded_image->set(row, col, value);
        }
      }

      return threholded_image;
    }
};
