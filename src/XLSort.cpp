#include <iostream>
#include <limits>
#include "XLSort.h"
#include "XLLog.h"

float * _input;

void merge_results(int left_index, int middle_index, int right_index) {
	int left_n = middle_index - left_index + 1;
	int right_n = right_index - middle_index;

	float* left = new float[left_n + 1];
	float* right = new float[right_n + 1];

	for(int i = 0; i < left_n; ++i)
		left[i] = _input[left_index + i - 1];

	for(int j = 0; j < right_n; ++j)
		right[j] = _input[middle_index + j];

	left[left_n] = std::numeric_limits<float>::max();
	right[right_n] = std::numeric_limits<float>::max();

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

void merge_sort(int left_index, int right_index) {
	if(left_index < right_index) {
		float float_middle = (float)(left_index + right_index) / 2.0;		
		int middle_index = (int)float_middle;

		merge_sort(left_index, middle_index);
		merge_sort(middle_index + 1, right_index);
		merge_results(left_index, middle_index, right_index);
	}
}

void sort_m(float * input, int len) {
	_input = input;
	int left_index = 1;
	int right_index = len;
	merge_sort(left_index, right_index);
}

void XLSort::sort(float * input, int len) {	
	XLLog log;
	log.function_start("XLSort::sort", XLColor::FG_DEFAULT);
	if(len <= 1) return;

	sort_m(input, len);

	log.function_end("XLSort::sort", XLColor::FG_DEFAULT);
}
