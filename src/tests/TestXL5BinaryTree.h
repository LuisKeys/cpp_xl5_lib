#pragma once

#include <iostream>
#include "../XL5Log.h"
#include "../XL5BinaryTree.h"

class TestXL5BinaryTree {
	public:
		void test(int verbose) {
		 	XL5Log log;
		 	XL5BinaryTree tree;

		 	// Cormen page 295 sample tree
		 	XL5BinaryTreeNode* root = tree.create(12);

		 	XL5BinaryTreeNode* left = tree.add_left(5, root);
		 	tree.add_left(2, left);
		 	tree.add_right(9, left);

		 	XL5BinaryTreeNode* right = tree.add_right(18, root);
		 	XL5BinaryTreeNode* right_left = tree.add_left(15, right);
		 	tree.add_right(17, right_left);

		 	tree.add_right(19, right);

		 	tree.walk_all(root);

		 	if(verbose)
		 		log.separator(XL5Color::FG_YELLOW);

		 	XL5BinaryTreeNode* node = tree.search(18, root);
		 	if(node != NULL) {
		 		if(verbose)
					log.value("Found node key", node->get_key(), XL5Color::FG_BLUE);
		 	}
			else {
				if(verbose)
					log.value("Found node key", (float)NULL, XL5Color::FG_RED);
			}

			XL5BinaryTreeNode* ins_node = new XL5BinaryTreeNode(13);
			tree.insert_node(ins_node);

			if(verbose)
				log.separator(XL5Color::FG_YELLOW);

		 	tree.walk_all(root);

			tree.delete_node(left);

			if(verbose)
				log.separator(XL5Color::FG_YELLOW);

		 	tree.walk_all(root);

		 	if(verbose)
		 		log.separator(XL5Color::FG_YELLOW);

		 	tree.drop();

			log.function_end("Test binary tree (XL5BinaryTree) Passed Ok", XL5Color::BG_GREEN);
		}
};
