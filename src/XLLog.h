#pragma once

class XLLog {
	public:
		void array(const std::string& description, float * value, int len);
		void function_start(const std::string& input);
		void function_end(const std::string& input);
		void line(const std::string& input);
		void value(const std::string& description, int value);
		void value(const std::string& description, float value);
};