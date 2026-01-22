#include <iostream>

#include "BinarySearchTree.h"

int main()
{
	std::printf("\n[BST Init]\n");
	BinarySearchTree bst;

	std::printf("\n[Insert]\n");
	bst.Insert(100);
	bst.Insert(50);
	bst.Insert(200);
	bst.Insert(100);


	std::printf("\n[Clear]\n");
	if (bst.Clear())
	{
		std::printf("[Clear_Complete]\n");
	}
	else
	{
		std::printf("[Clear_Failed]\n");
	}

	return 0;
}