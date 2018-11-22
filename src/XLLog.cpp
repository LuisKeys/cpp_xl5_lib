#include <iostream>
#include <ctime>
#include "XLLog.h"

#define _num_of_visible_elements 10
#define _filler "..................."
#define _long_filler "......................................"


clock_t _begin = clock();
int _is_enabled = 1;
int __num_of_visible_elements = 10;

// Write an array with a partial of its first and last elements to the console
void XLLog::array(const std::string& description, float * value, int len, int color) {
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

// Write when a function ends and displays elapsed execution time to the console
void XLLog::function_end(const std::string& input, int color) {
	if(_is_enabled == 0) return;
	clock_t end = clock();
	double elapsed_secs = double(end - _begin) / CLOCKS_PER_SEC;
	_begin = clock();
	std::cout << "\033[" << color << "m" << "Finished " << input;
	std::cout << " - In: " << elapsed_secs << " s" << "\033[0m" << std::endl << std::endl;
}

// Write when a function start to execute to the console
void XLLog::function_start(const std::string& input, int color) {
	if(_is_enabled == 0) return;
	std::cout << "\033[" << color <<"m" << "Started " << input  << "\033[0m" << std::endl;
	_begin = clock();
}

// Write a line of text to the console
void XLLog::text(const std::string& input, int color) {
	if(_is_enabled == 0) return;
	std::cout << "\033[" << color <<"m" << input  << "\033[0m" << std::endl << std::endl;
}

// Write a line of text to the console without new line
void XLLog::text_line(const std::string& input, int color) {
	if(_is_enabled == 0) return;
	std::cout << "\033[" << color <<"m" << input  << "\033[0m";
}

// Write a separator line with dots to the console
void XLLog::separator(int color) {
	if(_is_enabled == 0) return;
	std::cout << "\033[" << color <<"m" << _long_filler  << "\033[0m" << std::endl << std::endl;
}

// Write a int value to the console
void XLLog::value(const std::string& description, int value, int color) {
	if(_is_enabled == 0) return;
	std::cout << "\033[" << color << "m" << description << ":" << value  << "\033[0m" << std::endl << std::endl;
}

// Write a float value to the console
void XLLog::value(const std::string& description, float value, int color) {
	if(_is_enabled == 0) return;
	std::cout << "\033[" << color << "m" << description << ":" << value  << "\033[0m" << std::endl << std::endl;
}

// Write a int value to the console without new line
void XLLog::value_line(const std::string& description, int value, int color) {
	if(_is_enabled == 0) return;
	std::cout << "\033[" << color << "m" << description << ":" << value  << "\033[0m";
}

// Write a float value to the console without new line
void XLLog::value_line(const std::string& description, float value, int color) {
	if(_is_enabled == 0) return;
	std::cout << "\033[" << color << "m" << description << ":" << value  << "\033[0m";
}
