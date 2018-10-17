#pragma once

class XLSummary {
	public:
		float max(float * input, int len);
		float sum(float * input, int len);
	private:
		float sum_result = 0;
	  float max_result = 0;
};