#pragma once

#include <iostream>
#include "../XLLog.h"
#include "../XLBinaryTree.h"

class TestXLBinaryTree {
	public:
		void test(int verbose) {
		 	XLLog log;
		 	XLBinaryTree tree;

		 	verbose = 1;

		 	// Cormen page 295 sample tree
		 	XLBinaryTreeNode* root = tree.create(12);
		 	
		 	XLBinaryTreeNode* left = tree.add_left(5, root);
		 	tree.add_left(2, left);
		 	tree.add_right(9, left);

		 	XLBinaryTreeNode* right = tree.add_right(18, root);		 	
		 	XLBinaryTreeNode* right_left = tree.add_left(15, right);
		 	tree.add_right(17, right_left);

		 	tree.add_right(19, right);

		 	tree.walk_all(root);

		 	if(verbose)
		 		log.separator(XLColor::FG_YELLOW);

		 	XLBinaryTreeNode* node = tree.search(18, root);
		 	if(node != NULL) {
		 		if(verbose)
					log.value("Found node key", node->get_key(), XLColor::FG_BLUE);
		 	}
			else {
				if(verbose)
					log.value("Found node key", (float)NULL, XLColor::FG_RED);
			}

			XLBinaryTreeNode* ins_node = new XLBinaryTreeNode(13);
			tree.insert_node(ins_node);

			if(verbose)
				log.separator(XLColor::FG_YELLOW);

		 	tree.walk_all(root);

			tree.delete_node(left);

			if(verbose)
				log.separator(XLColor::FG_YELLOW);

		 	tree.walk_all(root);

		 	if(verbose)
		 		log.separator(XLColor::FG_YELLOW);

		 	tree.drop();

			log.function_end("Test binary tree (XLBinaryTree) Passed Ok", XLColor::BG_GREEN);
		}
};