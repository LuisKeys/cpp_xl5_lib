#pragma once

#include "XLLog.h"
#include "XLBinaryTreeNode.h"
#define LOG_ENABLED 1

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

		void insert_node(XLBinaryTreeNode* node) {
			XLBinaryTreeNode* y = NULL;
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

		void delete_node(XLBinaryTreeNode* node) {
			if(node->get_left() == NULL) {
				_transplant(node, node->get_right());
			}
			else if(node->get_right() == NULL) {
				_transplant(node, node->get_left());
			}
			else {
				XLBinaryTreeNode* y = _tree_min(node->get_right());
				if(y->get_parent() != node) {
					_transplant(y, y->get_right());
					y->set_right(node->get_right());
					y->get_right()->set_parent(y);
				}
				_transplant(node, y);
				y->set_left(node->get_left());
				y->get_left()->set_parent(y);
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
				if(LOG_ENABLED == 1)
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
							if(LOG_ENABLED == 1)
								log.value("Node key", node->get_key(), XLColor::FG_RED);
							delete node;
						}

						node = 	NULL;
					}
				}
			}
		}

		void _transplant(XLBinaryTreeNode* node_orig, XLBinaryTreeNode* node_new) {
			if(node_orig->get_parent() == NULL) {
				_root = node_new;
			}
			else if(node_orig == node_orig->get_parent()->get_left()) {
				node_orig->get_parent()->set_left(node_new);
			}
			else {
				node_orig->get_parent()->set_right(node_new);
			}

			if(node_new != NULL) {
				node_new->set_parent(node_orig->get_parent());
			}
		}

		XLBinaryTreeNode* _tree_min(XLBinaryTreeNode* node) {
			while(node->get_left() != NULL) {
				node = node->get_left();
			}
			return node;
		}

		XLBinaryTreeNode* _tree_max(XLBinaryTreeNode* node) {
			while(node->get_right() != NULL) {
				node = node->get_right();
			}
			return node;
		}
};
