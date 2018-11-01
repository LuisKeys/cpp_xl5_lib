#pragma once

#include <iostream>
#include "../XLLog.h"
#include "../XLBinaryTree.h"

class TestXLBinaryTree {
	public:
		void test(int verbose) {
		 	XLLog log;
		 	XLBinaryTree tree;

		 	XLBinaryTreeNode* root = tree.create(15);
		 	XLBinaryTreeNode* left = tree.add_left(6, root);
		 	XLBinaryTreeNode* right = tree.add_right(18, root);
		 	XLBinaryTreeNode* left_left = tree.add_left(3, left);
		 	tree.add_left(2, left_left);
		 	tree.add_right(4, left_left);
		 	tree.add_right(7, left);
		 	tree.add_left(17, right);
		 	tree.add_right(20, right);

		 	tree.walk_all(root);
		 	XLBinaryTreeNode* node = tree.search(7, root);
		 	if(node != (XLBinaryTreeNode*)NULL)
				log.value("Found node key", node->get_key(), XLColor::FG_BLUE);
			else
				log.value("Found node key", (float)NULL, XLColor::FG_RED);

		 	//tree.drop();

			log.function_end("Test binary tree (XLBinaryTree) Passed Ok", XLColor::BG_GREEN);
		}
};