#pragma once

#include <iostream>
#include <tuple>
#include "../XL5Log.h"
#include "../XL5Image.h"
#include "../XL5ImageFilters.h"
#include "../XL5ImagePatterns.h"
#include "../XL5Rectangle.h"
#include "../XL5Summary.h"

#define MATRIX XL5Matrix<uint8_t> *
#define RECTANGLE XL5Rectangle<int> *

class TestXL5FastFaceRecognition {
  public:
    void test(int verbose) {
      XL5Log log;
      XL5ImagePatterns image_patterns;
      log.function_start("Start faces recognition training", XL5Color::FG_BLUE);

      image_patterns.load_paterns("./data/eyes/");
      image_patterns.drop_patterns();

      for(int person_id = 1; person_id < 6; ++person_id) {
        if(person_id != 2 && person_id != 4 && person_id != 6) {
          for(int posse_id = 1; posse_id < 11; ++posse_id) {
          _preprocess(person_id, posse_id);
          }
        }
      }

      log.function_end("End faces recognition training", XL5Color::FG_BLUE);
    }

  private:
    tuple<MATRIX, int, int> _get_horizontal_bw_histogram_peaks(MATRIX image_data) {
      MATRIX horizontal_histogram = new XL5Matrix<uint8_t>();
      int rows_count = image_data->rows_count();
      int cols_count = image_data->cols_count();
      int row_histogram_value = image_data->cols_count();
      uint8_t value;
      int max = 0;
      int max_row = 0;
      int* histograms = new int[rows_count];
      int eyes_row = 0;
      int mouth_row = 0;
      int* offsets = new int[2];
      int bandwidth = (int)((float)rows_count * 0.25);
      offsets[0] = (int)((float)rows_count * 0.35);
      offsets[1]= (int)((float)rows_count * 0.7);

      horizontal_histogram->create(rows_count, cols_count, MAX_BW_IMAGE_VALUE);


      for(int row = 0; row < rows_count; ++row) {
        row_histogram_value = 0;
        for(int col = 0; col < cols_count; ++col) {
          value = image_data->get(row, col);

          if(value == MIN_BW_IMAGE_VALUE)
            row_histogram_value++;
        }

        for(int col = 0; col < row_histogram_value; ++col) {
          horizontal_histogram->set(row, col, MIN_BW_IMAGE_VALUE);
        }

        histograms[row] = row_histogram_value;
      }

      for(int i = 0; i < 2; ++i) {
        max = numeric_limits<int>::min();
        max_row = 0;
        for(int row = offsets[i]; row < offsets[i] + bandwidth; ++row) {
          if(max < histograms[row]) {
            max = histograms[row];
            max_row = row;
          }
        }

        if(i == 0) { eyes_row = max_row;}
        if(i == 1) { mouth_row = max_row;}

        for(int col = 0; col < cols_count; ++col) {
          horizontal_histogram->set(max_row - 1, col, MID_BW_IMAGE_VALUE);
          horizontal_histogram->set(max_row, col, MID_BW_IMAGE_VALUE);
        }
      }

      for(int row = 0; row < rows_count; ++row) {
        for(int col = 0; col < cols_count; ++col) {
          value = image_data->get(row, col);
          if(value == MIN_BW_IMAGE_VALUE)
            horizontal_histogram->set(row, col, value);
        }
      }

      delete histograms;
      return make_tuple(horizontal_histogram, eyes_row, mouth_row);;
    }

    tuple<MATRIX, RECTANGLE, RECTANGLE, RECTANGLE> _get_scan_areas(MATRIX original_image_data, MATRIX bw_image_data, int eyes_row, int mouth_row) {
      MATRIX scan_areas_bw_image = new XL5Matrix<uint8_t>();
      RECTANGLE left_eye = new XL5Rectangle<int>();
      RECTANGLE right_eye = new XL5Rectangle<int>();
      RECTANGLE mouth = new XL5Rectangle<int>();
      int rows_count = original_image_data->rows_count();
      int cols_count = original_image_data->cols_count();
      int bandwidth = (int)((float)rows_count * 0.1);
      int eyes_border_offset = (int)((float)cols_count * 0.15);
      int eyes_central_offset = (int)((float)cols_count * 0.01);
      int mouth_border_offset = (int)((float)cols_count * 0.15);
      int cg_eyes_offset = (int)((float)cols_count * 0.15);
      int cg_mouth_offset = (int)((float)cols_count * 0.26);
      uint8_t value;
      XL5Summary summary;

      scan_areas_bw_image = original_image_data->clone();

      left_eye->set_top(summary.max(eyes_row - bandwidth, 0));
      left_eye->set_bottom(summary.min(eyes_row + bandwidth, rows_count - 1));
      left_eye->set_left(eyes_border_offset);
      left_eye->set_right((cols_count / 2) - eyes_central_offset);
      scan_areas_bw_image->render_rectangle(left_eye, MID_BW_IMAGE_VALUE);

      right_eye->set_top(left_eye->get_top());
      right_eye->set_bottom(left_eye->get_bottom());
      right_eye->set_left((cols_count / 2) + eyes_central_offset);
      right_eye->set_right(cols_count - eyes_border_offset);
      scan_areas_bw_image->render_rectangle(right_eye, MID_BW_IMAGE_VALUE);

      mouth->set_top(summary.max(mouth_row - bandwidth, 0));
      mouth->set_bottom(summary.min(mouth_row + bandwidth, rows_count - 1));
      mouth->set_left(mouth_border_offset);
      mouth->set_right(cols_count - mouth_border_offset);
      scan_areas_bw_image->render_rectangle(mouth, MID_BW_IMAGE_VALUE);

      int horiz_left_eye_cg = _get_horiz_cg(bw_image_data, left_eye);
      int horiz_right_eye_cg = _get_horiz_cg(bw_image_data, right_eye);
      int horiz_mouth_cg = _get_horiz_cg(bw_image_data, mouth);

      left_eye->set_top(summary.max(eyes_row - bandwidth / 1.5, 0));
      left_eye->set_bottom(summary.min(eyes_row + bandwidth / 1.5, rows_count - 1));
      left_eye->set_left(horiz_left_eye_cg - cg_eyes_offset);
      left_eye->set_right(horiz_left_eye_cg + cg_eyes_offset);
      scan_areas_bw_image->render_rectangle(left_eye, MID_BW_IMAGE_VALUE);

      right_eye->set_top(summary.max(eyes_row - bandwidth / 1.5, 0));
      right_eye->set_bottom(summary.min(eyes_row + bandwidth / 1.5, rows_count - 1));
      right_eye->set_left(horiz_right_eye_cg - cg_eyes_offset);
      right_eye->set_right(horiz_right_eye_cg + cg_eyes_offset);
      scan_areas_bw_image->render_rectangle(right_eye, MID_BW_IMAGE_VALUE);

      mouth->set_top(summary.max(mouth_row - bandwidth / 1.5, 0));
      mouth->set_bottom(summary.min(mouth_row + bandwidth / 1.5, rows_count - 1));
      mouth->set_left(horiz_mouth_cg - cg_mouth_offset);
      mouth->set_right(horiz_mouth_cg + cg_mouth_offset);
      scan_areas_bw_image->render_rectangle(mouth, MID_BW_IMAGE_VALUE);

      return make_tuple(scan_areas_bw_image, left_eye, right_eye, mouth);
    }

    int _get_horiz_cg(MATRIX bw_image_data, RECTANGLE rectangle) {
      int cg_x_acum = 0;
      int points_counter = 0;
      for(int row = rectangle->get_top(); row < rectangle->get_bottom(); ++row) {
        for(int col = rectangle->get_left(); col < rectangle->get_right(); ++col) {
          if(bw_image_data->get(row, col) == MIN_BW_IMAGE_VALUE) {
            cg_x_acum += col;
            points_counter++;
          }
        }
      }


      return (int)((float)cg_x_acum / (float)points_counter);
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
      MATRIX image_data = image.get_gray_channel_data();
      // image.save_pgm_gray(string("image_data_") + dest_file, image_data, "XL5 threholded gradients");

      MATRIX gradients = image_filters.get_vertical_gradient(image_data);
      // image.save_pgm_gray(string("gradients_") + dest_file, gradients, "XL5 threholded gradients");

      MATRIX gradients_all_black = image_filters.get_white_to_black(gradients);
      // image.save_pgm_gray(string("black_") + dest_file, gradients_all_black, "XL5 gradients all black");

      MATRIX gradients_b_g = image_filters.get_gray_to_black(gradients_all_black);
      // image.save_pgm_gray(string("BW_") + dest_file, gradients_b_g, "XL5 gradients b w");

      MATRIX gradients_b_w = image_filters.get_gray_to_white(gradients_b_g);
      // image.save_pgm_gray(string("BW_") + dest_file, gradients_b_w, "XL5 gradients b w");

      auto horiz_hist_result = _get_horizontal_bw_histogram_peaks(gradients_b_w);
      MATRIX horizontal_bw_histogram_peaks = get<0>(horiz_hist_result);
      int eyes_row = get<1>(horiz_hist_result);
      int mouth_row = get<2>(horiz_hist_result);
      // image.save_pgm_gray(string("horiz_hist_") + dest_file, horizontal_bw_histogram_peaks, "XL5 horiz hist B W image");

      auto get_scan_areas_result = _get_scan_areas(image_data, gradients_b_w, eyes_row, mouth_row);
      MATRIX scan_areas_bw = get<0>(get_scan_areas_result);
      RECTANGLE left_eye_area = get<1>(get_scan_areas_result);
      RECTANGLE right_eye_area = get<2>(get_scan_areas_result);
      RECTANGLE mouth_area = get<3>(get_scan_areas_result);
      image.save_pgm_gray(string("scan_areas_") + dest_file, scan_areas_bw, "XL5 scan areas B W image");

      // delete buffers
      delete image_data;
      delete gradients;
      delete gradients_all_black;
      delete gradients_b_g;
      delete gradients_b_w;
      delete horizontal_bw_histogram_peaks;
      delete scan_areas_bw;

      delete left_eye_area;
      delete right_eye_area;
      delete mouth_area;

    }
};
