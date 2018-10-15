#pragma once

class XLLog {
	public:
		void function_start(const std::string& input);
		void function_end(const std::string& input);
		void int_value(const std::string& description, int value);
};