#pragma once

#include <iostream>

template<class T>
class XL5Rectangle {
  public:
    XL5Rectangle() { }

    XL5Rectangle(T left, T top, T right, T bottom) {
      _left = left;
      _top = top;
      _right = right;
      _bottom = bottom;
    }

    T get_left() {
      return _left;
    }

    T get_top() {
      return _top;
    }

    T get_right() {
      return _right;
    }

    T get_bottom() {
      return _bottom;
    }

    void set_left(T left) {
      _left = left;
    }

    void set_top(T top) {
      _top = top;
    }

    void set_right(T right) {
      _right = right;
    }

    void set_bottom(T bottom) {
      _bottom = bottom;
    }

    T get_height() {
      return (_bottom - _top);
    }

    T get_width() {
      return (_right - _left);
    }

    T get_vertical_cg() {
      return (int)((float)(_bottom - _top) / 2.0 + _top);
    }

    T get_horizontal_cg() {
      return (int)((float)(_right - _left) / 2.0 + _left);
    }

    // Write rectangle values to the console
		void log(const string& description, int color, int decimals) {

			cout << "\033[" << color << "m" << description << "\033[0m" << endl;

			cout << "\033[" << color << "m" << "Left:" << "\033[0m";
			cout << "\033[" << color << "m" << fixed << setprecision(decimals) << _left << endl;

      cout << "\033[" << color << "m" << "Right:" << "\033[0m";
			cout << "\033[" << color << "m" << fixed << setprecision(decimals) << _right << endl;

      cout << "\033[" << color << "m" << "Top:" << "\033[0m";
			cout << "\033[" << color << "m" << fixed << setprecision(decimals) << _top << endl;

      cout << "\033[" << color << "m" << "Bottom:" << "\033[0m";
			cout << "\033[" << color << "m" << fixed << setprecision(decimals) << _bottom << endl;

      cout << "\033[" << color << "m" << "Width:" << "\033[0m";
			cout << "\033[" << color << "m" << fixed << setprecision(decimals) << get_width() << endl;

      cout << "\033[" << color << "m" << "Height:" << "\033[0m";
			cout << "\033[" << color << "m" << fixed << setprecision(decimals) << get_height() << endl;

      cout << "\033[" << color << "m" << "Horizontal cg:" << "\033[0m";
			cout << "\033[" << color << "m" << fixed << setprecision(decimals) << get_horizontal_cg() << endl;

      cout << "\033[" << color << "m" << "Vertical cg:" << "\033[0m";
			cout << "\033[" << color << "m" << fixed << setprecision(decimals) << get_vertical_cg() << endl;
			cout << "\033[" << color << "m" << "\033[0m" << endl;

		}

  private:
    T _left = 0;
    T _top = 0;
    T _right = 0;
    T _bottom = 0;
};
