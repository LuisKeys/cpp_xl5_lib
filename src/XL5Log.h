#pragma once
#include <iostream>
#include <ctime>


//Clean console
#define xl5_clear_console() printf("\033[H\033[J")

#define _num_of_visible_elements 10
#define _filler "..................."
#define _long_filler "......................................"

// Colors definitions to log in the console using different fg and bg colors
namespace XL5Color {
  enum Code {
    FG_DEFAULT = 39,
    FG_BLACK = 30,
    FG_RED = 31,
    FG_GREEN = 32,
    FG_YELLOW = 33,
    FG_BLUE = 34,
    FG_MAGENTA = 35,
    FG_CYAN = 36,
    FG_LIGHT_GRAY = 37,
    FG_DARK_GRAY = 90,
    FG_LIGHT_RED = 91,
    FG_LIGHT_GREEN = 92,
    FG_LIGHT_YELLOW = 93,
    FG_LIGHT_BLUE = 94,
    FG_LIGHT_MAGENTA = 95,
    FG_LIGHT_CYAN = 96,
    FG_WHITE = 97,
    BG_RED = 41,
    BG_GREEN = 42,
    BG_BLUE = 44,
    BG_DEFAULT = 49
  };
}

// Log object
class XL5Log {
	public:
    // Write an array with a partial of its first and last elements to the console
    template<typename T>
    void array(const std::string& description, T * value, int len, int color) {
    	if(_is_enabled == 0) return;
    	int internal_len = len;
    	if(len > _num_of_visible_elements * 2)
    		internal_len = _num_of_visible_elements;

    	for(int i = 0; i < internal_len; ++i) {
    		std::cout << "\033[" << color << "m" << description << "[" << i << "]" << " = " << value[i]  << "\033[0m" << std::endl	;
    	}

    	if(len > _num_of_visible_elements) {
    		for(int i = 0; i < 3; ++i)
    		std::cout << "\033[" << color << "m" << _filler  << "\033[0m" << std::endl;
    	}

    	if(len > _num_of_visible_elements) {
    		for(int i = len - _num_of_visible_elements; i < len; ++i) {
    			std::cout << "\033[" << color << "m" << description << "[" << i << "]" << " = " << value[i]  << "\033[0m" << std::endl;
    		}
    	}
    }

    // Write an exception description
		void exception_msg(const std::string& input);

    // Write when a function ends and displays elapsed execution time to the console
		void function_end(const std::string& input, int color);

    // Write when a function start to execute to the console
		void function_start(const std::string& input, int color);

    // Write a line of text to the console
		void text(const std::string& input, int color);

    // Write a line of text to the console without new line
		void text_line(const std::string& input, int color);

    // Write a separator line with dots to the console
    void separator(int color);

    // Write a int value to the console
		void value(const std::string& description, int value, int color);

    // Write a float value to the console
		void value(const std::string& description, float value, int color);

    // Write a int value to the console without new line
		void value_line(const std::string& description, int value, int color);

    // Write a float value to the console without new line
		void value_line(const std::string& description, float value, int color);

  private:
    int _is_enabled = 1;
};
