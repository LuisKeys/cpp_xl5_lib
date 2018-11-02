#pragma once

#include "XLLog.h"
#include "XLBinaryTreeNode.h"

class XLBinaryTree {
	public:
		XLBinaryTreeNode* create(float key) {
			_root = new XLBinaryTreeNode(key);	
			return _root;
		}

		XLBinaryTreeNode* add_left(float key, XLBinaryTreeNode* parent) {
			XLBinaryTreeNode* left = new XLBinaryTreeNode(key, parent);
			parent->set_left(left);
			left->set_is_left(1);
			return left;
		}

		XLBinaryTreeNode* add_right(float key, XLBinaryTreeNode* parent) {
			XLBinaryTreeNode* right = new XLBinaryTreeNode(key, parent);
			parent->set_right(right);
			right->set_is_left(0	);
			return right;
		}

		void walk_all(XLBinaryTreeNode* node) {
			_walk_all(node, 0);
		}

		XLBinaryTreeNode* search(float key, XLBinaryTreeNode* node) {
			XLLog log;
			while(1 == 1) {				
				if(node == NULL)
					return NULL;

				if(node->get_right() == NULL && node->get_key() < key)
					return NULL;

				if(node->get_left() == NULL && node->get_key() > key)
					return NULL;

				if(key < node->get_key())
					node = node->get_left();
				else
					node = node->get_right();

				if(node->get_key() == key)
					break;
			}

			return node;
		}

		void insert(XLBinaryTreeNode* node) {
			XLBinaryTreeNode* y = _root;
			XLBinaryTreeNode* x = _root;

			while(x != NULL) {
				y = x;

				if(node->get_key() < x->get_key()) {
					x = x->get_left();
				}
				else {
					x = x->get_right();
				}
			}

			node->set_parent(y);

			if(y == NULL) {
				_root = node;
			}
			else if(node->get_key() < y->get_key()) {
				y->set_left(node);
			}
			else {
				y->set_right(node);
			}
		}

		void drop() {
			_walk_all(_root, 1);
		}

	private:		
		XLBinaryTreeNode* _root = NULL;

		void _walk_all(XLBinaryTreeNode* node, int8_t clear) {
			XLLog log;
			if(node != NULL) 
			{
				log.value("Node key", node->get_key(), XLColor::FG_YELLOW);
				_walk_all(node->get_left(), clear);
				_walk_all(node->get_right(), clear);

				if(clear == 1) {
					if(node->get_left() == NULL && 
						 node->get_right() == NULL) {
						
						XLBinaryTreeNode* parent = node->get_parent();
						
						if(parent != NULL) {
							if(node->get_is_left() == 1) {
								parent->set_left(NULL);
							}
							else {
								parent->set_right(NULL);
							}
						}
						
						if(node != _root) {
							log.value("Node key", node->get_key(), XLColor::FG_RED);
							delete node;
						}

						node = 	NULL;
					}
				}
			}
		}

};
