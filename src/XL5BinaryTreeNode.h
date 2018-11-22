#pragma once

#include <iostream>
#include "XL5Log.h"

// Binary tree node object and all its related operations
class XL5BinaryTreeNode {
	public:
		// Default constructor
		XL5BinaryTreeNode() {
		}

		// Constructor with key parameter
		XL5BinaryTreeNode(float key) {
			_key = key;
		}

		// Constructor with key and parent parameters
		XL5BinaryTreeNode(float key, XL5BinaryTreeNode* parent) {
			_key = key;
			_parent = parent;
		}

		//Set the node key
		void set_key(float key) {
			_key = key;
		}

		// Set the node left child
		void set_left(XL5BinaryTreeNode * left) {
			_left = left;
		}

		// Set the node right child
		void set_right(XL5BinaryTreeNode * right) {
			_right = right;
		}

		// Set the node parent
		void set_parent(XL5BinaryTreeNode* parent) {
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
		XL5BinaryTreeNode* get_left() {
			return _left;
		}

		// Get right child
		XL5BinaryTreeNode* get_right() {
			return _right;
		}

		// Get parent
		XL5BinaryTreeNode* get_parent() {
			return _parent;
		}

		// Get is_left flag (1 means that it is a left node)
		int8_t get_is_left() {
			return _is_left;
		}

	private:
		XL5BinaryTreeNode* _left = (XL5BinaryTreeNode*)NULL;
		XL5BinaryTreeNode* _right = (XL5BinaryTreeNode*)NULL;
		XL5BinaryTreeNode* _parent = (XL5BinaryTreeNode*)NULL;
		float _key = (float)NULL;
		int8_t _is_left = -1;
};
