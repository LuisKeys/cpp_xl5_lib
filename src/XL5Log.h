#pragma once

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
		void array(const std::string& description, float * value, int len, int color);

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
};
