#pragma once

// Description: Aggregation algorigthms
class XL5Summary {
	public:

		// Calculates the max value in input array
		// input > array of floats
		// len > array length
		float max(float* input, int len);

		// Calculates the min value in input array
		// input > array of floats
		// len > array length
		float min(float* input, int len);

		// Calculates the total addition value in input array
		// input > array of floats
		// len > array length
		float sum(float* input, int len);

		// Returns min of two values a and b
		float min(int a, int b);

		// Returns max of two values a and b
		float max(int a, int b);
};
