#pragma once

#include "XLLog.h"
#include "XLBinaryTreeNode.h"

class XLBinaryTree {
	public:
		void create(float key) {
			XLBinaryTreeNode* root = new XLBinaryTreeNode();	
		}

		void clear() {
		}

		void drop() {
		}

	private:		
		XLBinaryTreeNode* _root = (XLBinaryTreeNode*)NULL;
};