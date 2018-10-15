#include <iostream>
#include <ctime>
#include "XLLog.h"

clock_t _begin = clock();
int is_enabled = 1;


void XLLog::line(const std::string& input) {	
	if(is_enabled == 0) return;
	std::cout << input << std::endl;
}
void XLLog::function_start(const std::string& input) {	
	if(is_enabled == 0) return;
	std::cout << "Started " << input << std::endl;
	_begin = clock();
}

void XLLog::function_end(const std::string& input) {	
	if(is_enabled == 0) return;
	clock_t end = clock();
	double elapsed_secs = double(end - _begin) / CLOCKS_PER_SEC;
	_begin = clock();
	std::cout << "Finished " << input << std::endl;
	std::cout << "In: " << elapsed_secs << " s" << std::endl;
}

void XLLog::value(const std::string& description, int value) {	
	if(is_enabled == 0) return;
	std::cout << description << ":" << value << std::endl;
}

void XLLog::value(const std::string& description, float value) {
	if(is_enabled == 0) return;
	std::cout << description << ":" << value << std::endl;
}

void XLLog::array(const std::string& description, float * value, int len) {	
	if(is_enabled == 0) return;
	for(int i = 0; i < len; ++i) {
		std::cout << description << "[" << i << "]" << " = " << value[i] << std::endl;	
	}	
}
