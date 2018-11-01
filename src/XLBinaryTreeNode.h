#pragma once

#include <iostream>
#include "XLLog.h"

class XLBinaryTreeNode {
	public:
		XLBinaryTreeNode() {
		}

		XLBinaryTreeNode(float key) {
			_key = key;
		}

		void set_key(float key) {
			_key = key;
		}

		void set_left(XLBinaryTreeNode * left) {
			_left = left;
		}

		void set_right(XLBinaryTreeNode * right) {
			_right = right;
		}

		void set_parent(XLBinaryTreeNode * parent) {
			_parent = parent;
		}

	private:
		XLBinaryTreeNode* _left = (XLBinaryTreeNode*)NULL;
		XLBinaryTreeNode* _right = (XLBinaryTreeNode*)NULL;
		XLBinaryTreeNode* _parent = (XLBinaryTreeNode*)NULL;
		float _key = (float)NULL;
};