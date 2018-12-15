#pragma once

#include <iostream>
#include <tuple>
#include "../XL5Image.h"
#include "../XL5ImageFilter.h"
#include "../XL5ImagePattern.h"
#include "../XL5Fuzzy.h"
#include "../XL5Log.h"
#include "../XL5MLLogisticRegression.h"
#include "../XL5Memory.h"
#include "../XL5Random.h"
#include "../XL5Rectangle.h"
#include "../XL5Summary.h"

#define MATRIX XL5Matrix<uint8_t>*
#define MATRIX_O XL5Matrix<uint8_t>
#define RECTANGLE XL5Rectangle<int>*

class TestXL5FaceData {
public:
    int person_id = 0.0;
    int posse_id = 0.0;

    int left_eye_x = 0.0;
    int left_eye_y = 0.0;

    int right_eye_x = 0.0;
    int right_eye_y = 0.0;

    int mouth_x = 0.0;
    int mouth_y = 0.0;

    int max_eyes_separation = 0.0;
    int max_eyes_mouth_separation = 0.0;
    int min_eyes_separation = 0.0;
    int min_eyes_mouth_separation = 0.0;

    int get_eyes_delta_x() {
      return right_eye_x - left_eye_x;
    }

    int get_eyes_delta_y() {
      return right_eye_y - left_eye_y;
    }

    int get_eyes_mouth_delta_y() {
      int vertical_eyes_cg = (int)((float)(right_eye_y - left_eye_y) / 2.0);
      return mouth_y - vertical_eyes_cg;
    }

    float get_face_hash() {
      int vertical_eyes_cg = (int)((float)(right_eye_y - left_eye_y) / 2.0);
      XL5Fuzzy fuzzy;
      float eyes_mouth_score = fuzzy.triangular_membership(get_eyes_mouth_delta_y(),
                                                           (float)max_eyes_mouth_separation,
                                                           (float)max_eyes_mouth_separation - (float)min_eyes_mouth_separation);

      float eyes_score = fuzzy.triangular_membership(get_eyes_delta_x(),
                                                          (float)max_eyes_separation,
                                                          (float)max_eyes_separation - (float)min_eyes_separation);

      // Global score
      float eyes_coef = 1.2;
      float eyes_mouth_coef = 0.8;
      float global_score = eyes_coef * eyes_mouth_score + eyes_mouth_coef * eyes_score;
      float global_score_norm = global_score / (eyes_coef + eyes_mouth_coef);
      return global_score_norm;
    }

    // Write face data values to the console
		void log(int color) {

      cout << "\033[" << color << "m" << "Person id:" << "\033[0m";
			cout << "\033[" << color << "m" << person_id << endl;
      cout << "\033[" << color << "m" << "Posse id:" << "\033[0m";
      cout << "\033[" << color << "m" << posse_id << endl;

      cout << "\033[" << color << "m" << "Left eye x:" << "\033[0m";
			cout << "\033[" << color << "m" << left_eye_x << endl;
      cout << "\033[" << color << "m" << "Left eye y:" << "\033[0m";
      cout << "\033[" << color << "m" << left_eye_y << endl;

			cout << "\033[" << color << "m" << "Right eye x:" << "\033[0m";
			cout << "\033[" << color << "m" << right_eye_x << endl;
      cout << "\033[" << color << "m" << "Right eye y:" << "\033[0m";
      cout << "\033[" << color << "m" << right_eye_y << endl;

      cout << "\033[" << color << "m" << "Mouth x:" << "\033[0m";
			cout << "\033[" << color << "m" << mouth_x << endl;
      cout << "\033[" << color << "m" << "Mouth y:" << "\033[0m";
      cout << "\033[" << color << "m" << mouth_y << endl;

      cout << "\033[" << color << "m" << "Eyes delta x:" << "\033[0m";
			cout << "\033[" << color << "m" << get_eyes_delta_x() << endl;
      cout << "\033[" << color << "m" << "Eyes delta y:" << "\033[0m";
      cout << "\033[" << color << "m" << get_eyes_delta_y() << endl;
      cout << "\033[" << color << "m" << "Eyes - mouth delta y:" << "\033[0m";
      cout << "\033[" << color << "m" << get_eyes_mouth_delta_y() << endl;

      cout << "\033[" << color << "m" << "Min eyes separation:" << "\033[0m";
      cout << "\033[" << color << "m" << min_eyes_separation << endl;
      cout << "\033[" << color << "m" << "Max eyes separation:" << "\033[0m";
			cout << "\033[" << color << "m" << max_eyes_separation << endl;
      cout << "\033[" << color << "m" << "Min eyes - mouth separation:" << "\033[0m";
      cout << "\033[" << color << "m" << min_eyes_mouth_separation << endl;
      cout << "\033[" << color << "m" << "Max eyes - mouth separation:" << "\033[0m";
      cout << "\033[" << color << "m" << max_eyes_mouth_separation << endl;

			cout << "\033[" << color << "m" << "\033[0m" << endl;
		}
};

class TestXL5FastFaceRecognition {
  public:
    void test(int verbose) {
      XL5Log log;
      log.function_start("Start faces recognition training", XL5Color::FG_BLUE);

      // Train mouthes recognition LR
      _traing_mouth_lr();

      // Generate faces DB
      _generate_faces_db();

      log.function_end("End faces recognition training", XL5Color::FG_BLUE);

      log.function_start("Start faces recognition test with fuzzy logic", XL5Color::FG_BLUE);

      // test with fuzzy logic
      _test_faces();

      log.function_end("End faces recognition training test with fuzzy logic", XL5Color::FG_BLUE);
      // Clean all buffers and its elements

      _clean_buffers();
    }

    void _traing_mouth_lr() {
      XL5ImagePattern patterns;
      patterns.load_patterns("./data/mouths/");
      _lr = patterns.train_logistic_regression();
      patterns.drop();
    }

  private:
    XL5MLLogisticRegression<float>* _lr;
    XL5Stack<TestXL5FaceData*>* _faces_db;

    void _test_faces() {
      XL5Log log;
      for(int person_id = 1; person_id < 10; ++person_id) {
        if(person_id != 2 && person_id != 3 && person_id != 4 && person_id != 6) {
          for(int posse_id = 1; posse_id < 2; ++posse_id) {
            auto areas = _preprocess_face(person_id, posse_id);
            RECTANGLE left_eye_area = get<0>(areas);
            RECTANGLE right_eye_area = get<1>(areas);
            RECTANGLE mouth_area = get<2>(areas);

            TestXL5FaceData* face_data_test = _get_face_record(person_id, posse_id, mouth_area, left_eye_area, right_eye_area);

            for(int i = 0; i < _faces_db->size(); ++i) {
              TestXL5FaceData* face_data = _faces_db->get(i);
              face_data_test->max_eyes_separation = face_data->max_eyes_separation;
              face_data_test->max_eyes_mouth_separation = face_data->max_eyes_mouth_separation;
              face_data_test->min_eyes_separation = face_data->min_eyes_separation;
              face_data_test->min_eyes_mouth_separation = face_data->min_eyes_mouth_separation;

              float score_db = face_data->get_face_hash();
              float score_test = face_data_test->get_face_hash();
              if(score_db > 0.0 && score_test > 0.0 && abs(score_db - score_test) < 0.05) {
                log.text_line("Candidate found!", XL5Color::FG_GREEN);
                log.value_line(" - Score db:", score_db, XL5Color::FG_GREEN);
                log.value_line(" - Score test:", score_test, XL5Color::FG_GREEN);
                log.value_line(" - Test id:", face_data_test->person_id, XL5Color::FG_GREEN);
                log.value(" - Candidate id:", face_data->person_id, XL5Color::FG_GREEN);
              }
              else {
                if(face_data_test->person_id == face_data->person_id) {
                  log.text_line("Candidate not found!", XL5Color::FG_YELLOW);
                  log.value_line(" - Score db:", score_db, XL5Color::FG_YELLOW);
                  log.value_line(" - Score test:", score_test, XL5Color::FG_YELLOW);
                  log.value_line(" - Test id:", face_data_test->person_id, XL5Color::FG_YELLOW);
                  log.value(" - Candidate id:", face_data->person_id, XL5Color::FG_YELLOW);
                }
              }
            }

            XL5Memory::delete_object();
            delete face_data_test;

            XL5Memory::delete_object();
            delete left_eye_area;

            XL5Memory::delete_object();
            delete right_eye_area;

            XL5Memory::delete_object();
            delete mouth_area;
          }
        }
      }
    }

    void _generate_faces_db() {
      XL5Memory::new_object();
      _faces_db = new XL5Stack<TestXL5FaceData*>();
      _faces_db->create(100, 100);
      for(int person_id = 1; person_id < 10; ++person_id) {
        if(person_id != 2 && person_id != 3 && person_id != 4 && person_id != 6) {
          for(int posse_id = 1; posse_id < 5; ++posse_id) {
            auto areas = _preprocess_face(person_id, posse_id);
            RECTANGLE left_eye_area = get<0>(areas);
            RECTANGLE right_eye_area = get<1>(areas);
            RECTANGLE mouth_area = get<2>(areas);
            _add_face_record(person_id, posse_id, mouth_area, left_eye_area, right_eye_area);

            XL5Memory::delete_object();
            delete left_eye_area;

            XL5Memory::delete_object();
            delete right_eye_area;

            XL5Memory::delete_object();
            delete mouth_area;
          }
        }
      }

      // Get mins and maxs
      for(int person_id = 0; person_id < 20; ++person_id) {
        int max_eyes_separation = 0.0;
        int max_eyes_mouth_separation = 0.0;
        int min_eyes_separation = numeric_limits<int>::max();
        int min_eyes_mouth_separation = numeric_limits<int>::max();
        TestXL5FaceData* face_data = NULL;

        for(int i = 0; i < _faces_db->size(); ++i) {
          face_data = _faces_db->get(i);
          if(person_id == face_data->person_id) {
            if(max_eyes_separation < face_data->get_eyes_delta_x()) {
              max_eyes_separation = face_data->get_eyes_delta_x();
            }

            if(max_eyes_mouth_separation < face_data->get_eyes_mouth_delta_y()) {
              max_eyes_mouth_separation = face_data->get_eyes_mouth_delta_y();
            }

            if(min_eyes_separation > face_data->get_eyes_delta_x()) {
              min_eyes_separation = face_data->get_eyes_delta_x();
            }

            if(min_eyes_mouth_separation > face_data->get_eyes_mouth_delta_y()) {
              min_eyes_mouth_separation = face_data->get_eyes_mouth_delta_y();
            }
          }
        }

        for(int i = 0; i < _faces_db->size(); ++i) {
          face_data = _faces_db->get(i);
          if(person_id == face_data->person_id) {
            face_data->min_eyes_separation = min_eyes_separation;
            face_data->max_eyes_separation = max_eyes_separation;
            face_data->min_eyes_mouth_separation = min_eyes_mouth_separation;
            face_data->max_eyes_mouth_separation = max_eyes_mouth_separation;
          }
        }
      }

      for(int i = 0; i < _faces_db->size(); ++i) {
          TestXL5FaceData* face_data = _faces_db->get(i);
          face_data->log(XL5Color::FG_GREEN);
      }
    }

    tuple<RECTANGLE, RECTANGLE, RECTANGLE> _preprocess_face(int person_id, int posse_id) {
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

      // left_eye_area->log("left_eye_area", XL5Color::FG_YELLOW, 2);
      // image.save_pgm_gray(string("scan_areas_") + dest_file, scan_areas_bw, "XL5 scan areas B W image");

      // delete buffers
      XL5Memory::delete_object();
      image_data->drop();
      delete image_data;

      XL5Memory::delete_object();
      gradients->drop();
      delete gradients;

      XL5Memory::delete_object();
      gradients_all_black->drop();
      delete gradients_all_black;

      XL5Memory::delete_object();
      gradients_b_g->drop();
      delete gradients_b_g;

      XL5Memory::delete_object();
      gradients_b_w->drop();
      delete gradients_b_w;

      XL5Memory::delete_object();
      horizontal_bw_histogram_peaks->drop();
      delete horizontal_bw_histogram_peaks;

      XL5Memory::delete_object();
      scan_areas_bw->drop();
      delete scan_areas_bw;

      return make_tuple(left_eye_area, right_eye_area, mouth_area);
    }

    tuple<MATRIX, int, int> _get_horizontal_bw_histogram_peaks(MATRIX image_data) {
      XL5Memory::new_object();
      MATRIX horizontal_histogram = new XL5Matrix<uint8_t>();

      int rows_count = image_data->rows_count();
      int cols_count = image_data->cols_count();
      int row_histogram_value = image_data->cols_count();
      uint8_t value;
      int max = 0;
      int max_row = 0;

      XL5Memory::new_object();
      int* histograms = new int[rows_count];
      int eyes_row = 0;
      int mouth_row = 0;

      XL5Memory::new_object();
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

      XL5Memory::delete_object();
      delete histograms;
      return make_tuple(horizontal_histogram, eyes_row, mouth_row);;
    }

    tuple<MATRIX, RECTANGLE, RECTANGLE, RECTANGLE> _get_scan_areas(MATRIX original_image_data, MATRIX bw_image_data, int eyes_row, int mouth_row) {
      XL5Memory::new_object();
      MATRIX scan_areas_bw_image = new XL5Matrix<uint8_t>();

      XL5Memory::new_object();
      RECTANGLE left_eye = new XL5Rectangle<int>();

      XL5Memory::new_object();
      RECTANGLE right_eye = new XL5Rectangle<int>();

      XL5Memory::new_object();
      RECTANGLE mouth = new XL5Rectangle<int>();

      int rows_count = original_image_data->rows_count();
      int cols_count = original_image_data->cols_count();
      int bandwidth = (int)((float)rows_count * 0.1);
      int eyes_border_offset = (int)((float)cols_count * 0.1);
      int eyes_central_offset = (int)((float)cols_count * 0.01);
      int mouth_border_offset = (int)((float)cols_count * 0.15);
      int cg_eyes_offset = (int)((float)cols_count * 0.15);
      int cg_mouth_offset = (int)((float)cols_count * 0.3);
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

      left_eye = _find_eye(original_image_data, left_eye);
      scan_areas_bw_image->render_rectangle(left_eye, MIN_BW_IMAGE_VALUE);

      right_eye = _find_eye(original_image_data, right_eye);
      scan_areas_bw_image->render_rectangle(right_eye, MIN_BW_IMAGE_VALUE);

      mouth = _find_mouth(original_image_data, mouth);
      scan_areas_bw_image->render_rectangle(mouth, MIN_BW_IMAGE_VALUE);

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

    RECTANGLE _find_eye(MATRIX original_image_data, RECTANGLE eye_draft) {
      int rows_count = original_image_data->rows_count();
      int rectangle_side = (int)((float)rows_count * 0.05);
      int max_concentration = 0;
      int concentration = 0;
      int max_col = 0;
      int max_row = 0;

      for(int row = eye_draft->get_top(); row < eye_draft->get_bottom() - rectangle_side; ++row) {
        for(int col = eye_draft->get_left(); col < eye_draft->get_right() - rectangle_side; ++col) {
          concentration = 0;

          for(int row_inner = row; row_inner < row + rectangle_side; ++row_inner) {
            for(int col_inner = col; col_inner < col + rectangle_side; ++col_inner) {
              concentration += MAX_BW_IMAGE_VALUE - original_image_data->get(row_inner, col_inner);
            }
          }

          if(max_concentration < concentration) {
            max_concentration = concentration;
            max_col = col;
            max_row = row;
          }
        }
      }

      eye_draft->set_left(max_col);
      eye_draft->set_top(max_row);
      eye_draft->set_right(max_col + rectangle_side);
      eye_draft->set_bottom(max_row + rectangle_side);

      return eye_draft;
    }

    RECTANGLE _find_mouth(MATRIX original_image_data, RECTANGLE mouth_draft) {
      int scan_height = 12;
      int scan_width = 38;
      float estimation = 0.0;
      float max_estimation = 0.0;
      int max_row = 0;
      int max_col = 0;

      // Move a rectangle of scan_height x scan_width inside the mouth draft rectangle
      // Get max estimation probability as better location for mouth
      XL5Memory::new_object();
      RECTANGLE scan_area = new XL5Rectangle<int>();
      for(int row = mouth_draft->get_top(); row < mouth_draft->get_bottom() - scan_height; ++row) {
        for(int col = mouth_draft->get_left(); col < mouth_draft->get_right() - scan_width; ++col) {
          scan_area->set_left(col);
          scan_area->set_top(row);
          scan_area->set_right(col + scan_width);
          scan_area->set_bottom(row + scan_height);
          // Get scan area from image and clone to float
          XL5Matrix<float>* original_image_data_float = original_image_data->get_area_to_float(scan_area);

          // change from rectangle to horizontal matrix layout
          XL5Matrix<float>* Xlh = original_image_data_float->linear_horizontal();

          // normalize to [-1.0; 1.0]
          Xlh->normalize(-1.0, 1.0, 0.0, 255.0);

          _lr->predict(Xlh);
          estimation = _lr->get_non_rounded_estimation();

          if(max_estimation < estimation) {
            max_estimation = estimation;
            max_col = col;
            max_row = row;
            // std::cout << "max_estimation" << '\n';
            // std::cout << max_estimation << '\n';
            // std::cout << max_col << '\n';
            // std::cout << max_row << '\n';
          }

          Xlh->drop();
          XL5Memory::delete_object();
          delete Xlh;

          original_image_data_float->drop();
          XL5Memory::delete_object();
          delete original_image_data_float;
        }
      }

      XL5Memory::delete_object();
      delete scan_area;

      mouth_draft->set_left(max_col);
      mouth_draft->set_top(max_row);
      mouth_draft->set_right(max_col + scan_width);
      mouth_draft->set_bottom(max_row + scan_height);

      return mouth_draft;
    }

    void _add_face_record(int person_id, int posse_id, RECTANGLE mouth, RECTANGLE left_eye, RECTANGLE right_eye) {

      TestXL5FaceData* face_data = _get_face_record(person_id, posse_id, mouth, left_eye, right_eye);

      _faces_db->push(face_data);
    }

    TestXL5FaceData* _get_face_record(int person_id, int posse_id, RECTANGLE mouth, RECTANGLE left_eye, RECTANGLE right_eye) {
      XL5Memory::new_object();
      TestXL5FaceData* face_date = new TestXL5FaceData();
      face_date->person_id = person_id;
      face_date->posse_id = posse_id;

      face_date->mouth_x = mouth->get_horizontal_cg();
      face_date->mouth_y = mouth->get_vertical_cg();

      face_date->left_eye_x = left_eye->get_horizontal_cg();
      face_date->left_eye_y = left_eye->get_vertical_cg();

      face_date->right_eye_x = right_eye->get_horizontal_cg();
      face_date->right_eye_y = right_eye->get_vertical_cg();
      // face_date->log(XL5Color::FG_BLUE);
    }

    void _clean_buffers() {
      _lr->drop();
      XL5Memory::delete_object();
      delete _lr;

      for(int i = 0; i < _faces_db->size(); ++i) {
        TestXL5FaceData* face_data = _faces_db->get(i);
        XL5Memory::delete_object();
        delete face_data;
      }

      _faces_db->drop();
      XL5Memory::delete_object();
      delete _faces_db;
    }
};
