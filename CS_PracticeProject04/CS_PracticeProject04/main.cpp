#include <iostream>

#include "BinarySearchTree.h"

int main()
{
	std::printf("\n[BST Init]\n");
	BinarySearchTree bst;
	bst.Insert(100);
	bst.Insert(50);
	bst.Insert(200);
	bst.Insert(100);

	return 0;
}