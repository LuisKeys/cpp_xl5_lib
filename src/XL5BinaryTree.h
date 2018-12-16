#pragma once

#include "XL5Log.h"
#include "XL5BinaryTreeNode.h"
#include "XL5Memory.h"

#define LOG_ENABLED 1
// Binary tree object and all its related operations
class XL5BinaryTree {
	public:
		// Create a tree with a root node with the provided key
		XL5BinaryTreeNode* create(float key) {
			XL5Memory::new_object();
			_root = new XL5BinaryTreeNode(key);
			return _root;
		}

		// Add left node to a provided parent node with a given key
		XL5BinaryTreeNode* add_left(float key, XL5BinaryTreeNode* parent) {
			XL5Memory::new_object();
			XL5BinaryTreeNode* left = new XL5BinaryTreeNode(key, parent);
			parent->set_left(left);
			left->set_is_left(1);
			return left;
		}

		// Add right node to a provided parent node with a given key
		XL5BinaryTreeNode* add_right(float key, XL5BinaryTreeNode* parent) {
			XL5Memory::new_object();
			XL5BinaryTreeNode* right = new XL5BinaryTreeNode(key, parent);
			parent->set_right(right);
			right->set_is_left(0	);
			return right;
		}

		// Walk through all the tree and prints its keys in recursive order
		void walk_all(XL5BinaryTreeNode* node) {
			_walk_all(node, 0);
		}

		// Search a particular key and returns the node
		XL5BinaryTreeNode* search(float key, XL5BinaryTreeNode* node) {
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

		// Insert a given node in the tree based on its key value
		void insert_node(XL5BinaryTreeNode* node) {
			XL5BinaryTreeNode* y = NULL;
			XL5BinaryTreeNode* x = _root;

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

		// Delete a given node from the tree
		void delete_node(XL5BinaryTreeNode* node) {
			if(node->get_left() == NULL) {
				_transplant(node, node->get_right());
			}
			else if(node->get_right() == NULL) {
				_transplant(node, node->get_left());
			}
			else {
				XL5BinaryTreeNode* y = _tree_min(node->get_right());
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

		// Drop the tree from memory
		void drop() {
			_walk_all(_root, 1);
		}

	private:
		XL5BinaryTreeNode* _root = NULL;

		void _walk_all(XL5BinaryTreeNode* node, int8_t clear) {
			XL5Log log;
			if(node != NULL)
			{
				if(LOG_ENABLED == 1)
					log.value("Node key", node->get_key(), XL5Color::FG_YELLOW);

				_walk_all(node->get_left(), clear);
				_walk_all(node->get_right(), clear);

				if(clear == 1) {
					if(node->get_left() == NULL &&
						 node->get_right() == NULL) {

						XL5BinaryTreeNode* parent = node->get_parent();

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
								log.value("Node key", node->get_key(), XL5Color::FG_RED);

							XL5Memory::delete_object();
							delete node;
						}

						node = 	NULL;
					}
				}
			}
		}

		void _transplant(XL5BinaryTreeNode* node_orig, XL5BinaryTreeNode* node_new) {
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

		XL5BinaryTreeNode* _tree_min(XL5BinaryTreeNode* node) {
			while(node->get_left() != NULL) {
				node = node->get_left();
			}
			return node;
		}

		XL5BinaryTreeNode* _tree_max(XL5BinaryTreeNode* node) {
			while(node->get_right() != NULL) {
				node = node->get_right();
			}
			return node;
		}
};
