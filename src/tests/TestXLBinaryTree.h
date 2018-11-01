#pragma once

#include <iostream>
#include "../XLLog.h"
#include "../XLBinaryTree.h"

class TestXLBinaryTree {
	public:
		void test(int verbose) {
		 	XLLog xlLog;
		 	XLBinaryTree tree;

			xlLog.function_end("Test binary tree (XLBinaryTree) Passed Ok", XLColor::BG_GREEN);
		}
};