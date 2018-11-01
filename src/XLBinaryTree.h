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
				if(node == (XLBinaryTreeNode*) NULL)
					return (XLBinaryTreeNode*) NULL;

				if(node->get_right() == (XLBinaryTreeNode*) NULL && node->get_key() < key)
					return (XLBinaryTreeNode*) NULL;

				if(node->get_left() == (XLBinaryTreeNode*) NULL && node->get_key() > key)
					return (XLBinaryTreeNode*) NULL;

				if(key < node->get_key())
					node = node->get_left();
				else
					node = node->get_right();

				if(node->get_key() == key)
					break;
			}

			return node;
		}

		void drop() {
			_walk_all(_root, 1);
		}

	private:		
		XLBinaryTreeNode* _root = (XLBinaryTreeNode*)NULL;

		void _walk_all(XLBinaryTreeNode* node, int8_t clear) {
			XLLog log;
			if(node != (XLBinaryTreeNode*)NULL) 
			{
				log.value("Node key:", node->get_key(), XLColor::FG_YELLOW);
				_walk_all(node->get_left(), clear);
				_walk_all(node->get_right(), clear);

				if(clear == 1) {
					if(node->get_left() == (XLBinaryTreeNode*)NULL && 
						 node->get_right() == (XLBinaryTreeNode*)NULL) {
						
						XLBinaryTreeNode* parent = node->get_parent();
						
						if(parent != (XLBinaryTreeNode*)NULL) {
							if(node->get_is_left() == 1) {
								parent->set_left((XLBinaryTreeNode*)NULL);
							}
							else {
								parent->set_right((XLBinaryTreeNode*)NULL);
							}
						}
						
						if(node != _root) {
							log.value("Node key:", node->get_key(), XLColor::FG_RED);
							delete node;
						}

						node = (XLBinaryTreeNode*)NULL;
					}
				}
			}
		}

};
