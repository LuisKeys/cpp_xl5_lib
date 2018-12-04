#pragma once

#include <iostream>
#include <limits>
#include "XL5Matrix.h"

#define MAX_VALUE 255
#define MID_VALUE 128

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

    XL5Matrix<uint8_t> * get_horizontal_bw_histogram_peaks(XL5Matrix<uint8_t> * image_data) {
      XL5Matrix<uint8_t> * horizontal_histogram = new XL5Matrix<uint8_t>();
      int rows_count = image_data->rows_count();
      int cols_count = image_data->cols_count();
      int row_histogram_value = image_data->cols_count();
      uint8_t value;
      int min = 0;
      int min_row = 0;
      int* histograms = new int[rows_count];
      int* offsets = new int[2];
      int bandwidth = (int)((float)rows_count * 0.25);
      offsets[0] = (int)((float)rows_count * 0.35);
      offsets[1]= (int)((float)rows_count * 0.7);

      horizontal_histogram->create(rows_count, cols_count);


      for(int row = 0; row < rows_count; ++row) {
        row_histogram_value = 0;
        for(int col = 0; col < cols_count; ++col) {
          value = image_data->get(row, col);

          if(value == MAX_VALUE)
            row_histogram_value++;
        }


        for(int col = 0; col < row_histogram_value; ++col) {
          horizontal_histogram->set(row, col, MAX_VALUE);
        }

        histograms[row] = row_histogram_value;
      }

      for(int i = 0; i < 2; ++i) {
        min = numeric_limits<int>::max();
        min_row = 0;
        for(int row = offsets[i]; row < offsets[i] + bandwidth; ++row) {
          if(min > histograms[row]) {
            min = histograms[row];
            min_row = row;
          }
        }

        for(int col = 0; col < cols_count; ++col) {
          horizontal_histogram->set(min_row - 1, col, MID_VALUE);
          horizontal_histogram->set(min_row, col, MID_VALUE);
        }
      }

      for(int row = 0; row < rows_count; ++row) {
        for(int col = 0; col < cols_count; ++col) {
          value = image_data->get(row, col);
          if(value == 0)
            horizontal_histogram->set(row, col, value);
        }
      }

      delete histograms;
      return horizontal_histogram;
    }


    XL5Matrix<uint8_t> * get_threhold(XL5Matrix<uint8_t> * image_data, int threhold) {
      XL5Matrix<uint8_t> * threholded_gradients = new XL5Matrix<uint8_t>();
      int rows_count = image_data->rows_count();
      int cols_count = image_data->cols_count();
      uint8_t value;
      threholded_gradients->create(rows_count, cols_count);

      for(int row = 1; row < rows_count - 1; ++row) {
        for(int col = 1; col < cols_count - 1; ++col) {
          value = image_data->get(row, col - 1);

          if(value > threhold)
            value = MAX_VALUE;
          else
            value = 0;
          threholded_gradients->set(row, col, value);
        }
      }

      return threholded_gradients;
    }

    XL5Matrix<uint8_t> * get_horizontal_gradient(XL5Matrix<uint8_t> * image_data) {
      XL5Matrix<uint8_t> * horiz_gradients = new XL5Matrix<uint8_t>();
      int rows_count = image_data->rows_count();
      int cols_count = image_data->cols_count();
      uint8_t left_pixel = 0;
      uint8_t right_pixel = 0;
      uint8_t scaled_diff = 0;

      if(rows_count < 1 || cols_count < 3)
         return horiz_gradients;

      horiz_gradients->create(rows_count, cols_count);

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
      XL5Matrix<uint8_t> * vertical_gradients = new XL5Matrix<uint8_t>();
      int rows_count = image_data->rows_count();
      int cols_count = image_data->cols_count();
      uint8_t top_pixel = 0;
      uint8_t bottom_pixel = 0;
      uint8_t scaled_diff = 0;

      if(rows_count < 3 || cols_count < 1)
         return vertical_gradients;

      vertical_gradients->create(rows_count, cols_count);

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
      XL5Matrix<uint8_t> * threholded_image = new XL5Matrix<uint8_t>();
      int rows_count = image_data->rows_count();
      int cols_count = image_data->cols_count();
      uint8_t value;
      threholded_image->create(rows_count, cols_count);

      for(int row = 1; row < rows_count - 1; ++row) {
        for(int col = 1; col < cols_count - 1; ++col) {
          value = image_data->get(row, col - 1);
          if(is_increase == 1) {
            if(value > threhold)
              value = MAX_VALUE;
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
