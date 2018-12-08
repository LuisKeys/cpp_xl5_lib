#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "XL5Matrix.h"

#define VERBOSE 0

using namespace std;
// Images object and its related basic operations
class XL5Image {
  public:
    // Get a gray scale PGM data
    XL5Matrix<uint8_t>* get_gray_channel_data() {
        return _gray_channel;
    }

    // Load a PGM file
    int load_pgm(const string& image_path) {

      if(VERBOSE == 1)
        cout << image_path << endl;

      ifstream image_file(image_path, ifstream::in);
      string input_line = "";
      string input_line2 = "";
      string width_str = "";
      string height_str = "";

      // First line : version
      getline(image_file, input_line);
      if(VERBOSE == 1)
        cout << "Version : " << input_line << endl;
      if(input_line == "P2") {
        _type = 2;

        if(VERBOSE == 1)
          cout << "Portable GrayMap - ASCII" << endl;
      }

      if(input_line == "P5") {
        _type = 5;

        if(VERBOSE == 1)
          cout << "Portable GrayMap - Binary" << endl;
      }

      // Second line : comment or size if no comment
      getline(image_file, input_line);
      if(input_line.find("#") == 0) {
        // Comment found
        _comment = input_line;

        // Third line : size
        image_file >> input_line >> input_line2;
        _width = stoi(input_line);
        _height = stoi(input_line2);
      }
      else {
        int found_index = input_line.find(" ");
        width_str = input_line.substr(0, found_index);
        _width = stoi(input_line);
        height_str = input_line.substr(found_index + 1);
        _height = stoi(height_str);
      }

      // Third line : maximum value
      image_file >> input_line;
      _maximum_value = stoi(input_line);

      if(VERBOSE == 1) {
        cout << "Commment:" << _comment << endl;
        cout << "Width:" << _width << endl;
        cout << "Height:" << _height << endl;
        cout << "Maximum_value:" << _maximum_value << endl;
      }

      if(_type == 2) {
        _gray_channel = new XL5Matrix<uint8_t>();
        _gray_channel->create(_height, _width, 0);
        char byte_buffer = 0;
        float float_buffer = 0;
        for(int row = 0; row < _height; ++row) {
          for(int col = 0; col < _width; ++col) {
            image_file.read(&byte_buffer, 1);
            int value;
            image_file >> value;
            float_buffer = (float)value;
            float_buffer *= 255.0 / _maximum_value;
            _gray_channel->set(row, col, (uint8_t)float_buffer);
          }
        }
      }

      if(_type == 5) {
        _gray_channel = new XL5Matrix<uint8_t>();
        _gray_channel->create(_height, _width, 0);
        char byte_buffer = 0;
        float float_buffer = 0;
        for(int row = 0; row < _height; ++row) {
          for(int col = 0; col < _width; ++col) {
            image_file.read(&byte_buffer, 1);
            float_buffer = (float)byte_buffer;
            float_buffer *= 255.0 / _maximum_value;
            _gray_channel->set(row, col, (uint8_t)float_buffer);
          }
        }
      }

      return _type;
    }

    // Save a PGM file
    void save_pgm_gray(const string& image_path, XL5Matrix<uint8_t>* data, string comment) {
      ofstream image_file;
      int count_per_line = 0;

      _width = data->cols_count();
      _height = data->rows_count();

      image_file.open (image_path);
      image_file << "P2 " << endl;
      image_file << to_string(_width) << " " << to_string(_height) << endl;
      image_file << "255" << endl;


      for(int row = 0; row < _height; ++row) {
        for(int col = 0; col < _width; ++col) {
          if(count_per_line > 50) {
            count_per_line = 0;
            image_file << endl;
          }

          image_file << to_string(data->get(row, col));
          if(count_per_line < 50) {
            image_file << " ";
          }
          ++count_per_line;
        }
      }

      image_file.close();
    }

    // Drop PGM image
    void drop_pgm_gray() {
      if(_type == 5)
        _gray_channel->drop();
    }

  private:
    XL5Matrix<uint8_t>* _gray_channel;
    string _pgm_version = "";
    string _comment = "";
    int _type = 0;
    int _height = 0;
    int _width = 0;
    int _maximum_value = 0;
};
