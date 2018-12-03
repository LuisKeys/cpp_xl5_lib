#include <iostream>
#include <limits>
#include "XL5Sort.h"
#include "XL5Log.h"

float * _input;

// Merge results
// left_index > left partition index
// middle_index > middle partition index
// right_index > right partition index
void merge_results(int left_index, int middle_index, int right_index) {
	int left_n = middle_index - left_index + 1;
	int right_n = right_index - middle_index;

	float* left = new float[left_n + 1];
	float* right = new float[right_n + 1];

	for(int i = 0; i < left_n; ++i)
		left[i] = _input[left_index + i - 1];

	for(int j = 0; j < right_n; ++j)
		right[j] = _input[middle_index + j];

	left[left_n] = numeric_limits<float>::max();
	right[right_n] = numeric_limits<float>::max();

	int i = 0, j = 0;

	for(int k = left_index - 1; k < right_index; ++k) {
		if(left[i] <= right[j]) {
			_input[k] = left[i];
			i++;
		}
		else {
			_input[k] = right[j];
			j++;
		}
	}
	delete left;
	delete right;
}

// Merge sort recursive function
// left_index > left partition index
// right_index > right partition index
void merge_sort(int left_index, int right_index) {
	if(left_index < right_index) {
		float float_middle = (float)(left_index + right_index) / 2.0;
		int middle_index = (int)float_middle;

		merge_sort(left_index, middle_index);
		merge_sort(middle_index + 1, right_index);
		merge_results(left_index, middle_index, right_index);
	}
}

// Merge sort private function which calls merge_sort recursive function
// input > float array
// len > float array length
void sort_m(float * input, int len) {
	_input = input;
	int left_index = 1;
	int right_index = len;
	merge_sort(left_index, right_index);
}

// Merge sort a float array
// input > float array
// len > float array length
void XL5Sort::sort(float * input, int len) {
	XL5Log log;
	log.function_start("XL5Sort::sort", XL5Color::FG_DEFAULT);
	if(len <= 1) return;

	sort_m(input, len);

	log.function_end("XL5Sort::sort", XL5Color::FG_DEFAULT);
}
