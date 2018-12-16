#include <iostream>
#include <ctime>
#include "XL5Log.h"

using namespace std;

clock_t _begin = clock();
int __num_of_visible_elements = 10;

// Write an exception description
void XL5Log::exception_msg(const string& input) {
	cout << "\033[" << XL5Color::FG_RED <<"m" << "* " << input  << " *" << "\033[0m" << endl;
}

// Write when a function ends and displays elapsed execution time to the console
void XL5Log::function_end(const string& input, int color) {
	if(_is_enabled == 0) return;
	clock_t end = clock();
	double elapsed_secs = double(end - _begin) / CLOCKS_PER_SEC;
	_begin = clock();
	cout << "\033[" << color << "m" << "Finished " << input;
	cout << " - In: " << elapsed_secs << " s" << "\033[0m" << endl << endl;
}

// Write when a function start to execute to the console
void XL5Log::function_start(const string& input, int color) {
	if(_is_enabled == 0) return;
	cout << "\033[" << color <<"m" << "Started " << input  << "\033[0m" << endl;
	_begin = clock();
}

// Write a line of text to the console
void XL5Log::text(const string& input, int color) {
	if(_is_enabled == 0) return;
	cout << "\033[" << color <<"m" << input  << "\033[0m" << endl << endl;
}

// Write a line of text to the console without new line
void XL5Log::text_line(const string& input, int color) {
	if(_is_enabled == 0) return;
	cout << "\033[" << color <<"m" << input  << "\033[0m";
}

// Write a separator line with dots to the console
void XL5Log::separator(int color) {
	if(_is_enabled == 0) return;
	cout << "\033[" << color <<"m" << _long_filler  << "\033[0m" << endl << endl;
}

// Write a int value to the console
void XL5Log::value(const string& description, int value, int color) {
	if(_is_enabled == 0) return;
	cout << "\033[" << color << "m" << description << ":" << value  << "\033[0m" << endl << endl;
}

// Write a float value to the console
void XL5Log::value(const string& description, float value, int color) {
	if(_is_enabled == 0) return;
	cout << "\033[" << color << "m" << description << ":" << value  << "\033[0m" << endl << endl;
}

// Write a int value to the console without new line
void XL5Log::value_line(const string& description, int value, int color) {
	if(_is_enabled == 0) return;
	cout << "\033[" << color << "m" << description << ":" << value  << "\033[0m";
}

// Write a float value to the console without new line
void XL5Log::value_line(const string& description, float value, int color) {
	if(_is_enabled == 0) return;
	cout << "\033[" << color << "m" << description << ":" << value  << "\033[0m";
}
