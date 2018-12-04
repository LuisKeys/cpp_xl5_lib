#pragma once

#include <iostream>
#include "../XL5Log.h"
#include "../XL5Image.h"
#include "../XL5ImageFilters.h"

class TestXL5Image {
  public:
    void test(int verbose) {
      XL5Log log;
      log.function_start("Start faces recognition training", XL5Color::FG_BLUE);

      for(int person_id = 1; person_id < 11; ++person_id) {
        if(person_id != 2 && person_id != 4 && person_id != 6) {
          for(int posse_id = 1; posse_id < 11; ++posse_id) {
          _preprocess(person_id, posse_id);
          }
        }
      }

      log.function_end("End faces recognition training", XL5Color::FG_BLUE);
    }

  private:
    XL5Matrix<uint8_t> * _get_horizontal_bw_histogram_peaks(XL5Matrix<uint8_t> * image_data) {
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

    void _preprocess(int person_id, int posse_id) {
      XL5Image image;
      XL5ImageFilters image_filters;
      string person_index = to_string(person_id);
      string posse_index = to_string(posse_id);
      string source_file = posse_index + string(".pgm");
      string dest_file = person_index + string("_") + posse_index + string(".pgm");
      string base_path = string("./data/att_faces/s") + person_index + string("/");

      int type = image.load_pgm(base_path + source_file);
      XL5Matrix<uint8_t>* image_data = image.get_gray_channel_data();

      XL5Matrix<uint8_t>* gradients = image_filters.get_vertical_gradient(image_data);
      // image.save_pgm_gray(string("gradients_") + dest_file, gradients, "XL5 threholded gradients");

      XL5Matrix<uint8_t>* gradients_all_black = image_filters.get_white_to_black(gradients);
      // image.save_pgm_gray(string("black_") + dest_file, gradients_all_black, "XL5 gradients all black");

      XL5Matrix<uint8_t>* gradients_b_g = image_filters.get_gray_to_black(gradients_all_black);
      // image.save_pgm_gray(string("BW_") + dest_file, gradients_b_g, "XL5 gradients b w");

      XL5Matrix<uint8_t>* gradients_b_w = image_filters.get_gray_to_white(gradients_b_g);
      // image.save_pgm_gray(string("BW_") + dest_file, gradients_b_w, "XL5 gradients b w");

      XL5Matrix<uint8_t>* horizontal_bw_histogram_peaks = _get_horizontal_bw_histogram_peaks(gradients_b_w);
      image.save_pgm_gray(string("horiz_hist_") + dest_file, horizontal_bw_histogram_peaks, "XL5 horizontal b w histogram peaks");

      // delete buffers
      delete image_data;
      delete gradients;
      delete gradients_all_black;
      delete gradients_b_g;
      delete gradients_b_w;
      delete horizontal_bw_histogram_peaks;

    }
};
