#include <iostream>
#include <ctime>
#include "XLLog.h"

clock_t _begin = clock();

void XLLog::function_start(const std::string& input) {	
	std::cout << "Started " << input << std::endl;
	_begin = clock();
}

void XLLog::function_end(const std::string& input) {	
	clock_t end = clock();
	double elapsed_secs = double(end - _begin) / CLOCKS_PER_SEC;
	_begin = clock();
	std::cout << "Finished " << input << std::endl;
	std::cout << "In: " << elapsed_secs << " s" << std::endl;
}

void XLLog::int_value(const std::string& description, int value) {	
	std::cout << description << ":" << value << std::endl;
}
