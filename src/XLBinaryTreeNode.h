#pragma once

#include <iostream>
#include "XLLog.h"

// Binary tree node object and all its related operations
class XLBinaryTreeNode {
	public:
		// Default constructor
		XLBinaryTreeNode() {
		}

		// Constructor with key parameter
		XLBinaryTreeNode(float key) {
			_key = key;
		}

		// Constructor with key and parent parameters
		XLBinaryTreeNode(float key, XLBinaryTreeNode* parent) {
			_key = key;
			_parent = parent;
		}

		//Set the node key
		void set_key(float key) {
			_key = key;
		}

		// Set the node left child
		void set_left(XLBinaryTreeNode * left) {
			_left = left;
		}

		// Set the node right child
		void set_right(XLBinaryTreeNode * right) {
			_right = right;
		}

		// Set the node parent
		void set_parent(XLBinaryTreeNode* parent) {
			_parent = parent;
		}

		// Set the is_left flag of the node (1 means that it is a left node)
		void set_is_left(int8_t is_left) {
			_is_left = is_left;
		}

		// Get node key
		float get_key() {
			return _key;
		}

		// Get left child
		XLBinaryTreeNode* get_left() {
			return _left;
		}

		// Get right child
		XLBinaryTreeNode* get_right() {
			return _right;
		}

		// Get parent
		XLBinaryTreeNode* get_parent() {
			return _parent;
		}

		// Get is_left flag (1 means that it is a left node)
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
