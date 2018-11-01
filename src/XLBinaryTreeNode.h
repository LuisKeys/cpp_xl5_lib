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

		XLBinaryTreeNode(float key, XLBinaryTreeNode* parent) {
			_key = key;
			_parent = parent;
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

		void set_parent(XLBinaryTreeNode* parent) {
			_parent = parent;
		}

		void set_is_left(int8_t is_left) {
			_is_left = is_left;
		}

		float get_key() {
			return _key;
		}

		XLBinaryTreeNode* get_left() {
			return _left;
		}

		XLBinaryTreeNode* get_right() {
			return _right;
		}

		XLBinaryTreeNode* get_parent() {
			return _parent;
		}

		int8_t get_is_left() {
			return _is_left;
		}

	private:
		XLBinaryTreeNode* _left = (XLBinaryTreeNode*)NULL;
		XLBinaryTreeNode* _right = (XLBinaryTreeNode*)NULL;
		XLBinaryTreeNode* _parent = (XLBinaryTreeNode*)NULL;
		float _key = (float)NULL;
		int8_t _is_left = -1;
};