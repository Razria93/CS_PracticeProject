#include <iostream>

#include "BinarySearchTree.h"

int main()
{
	std::printf("\n[BST Init]\n");
	BinarySearchTree bst;

	std::printf("\n[Insert]\n");
	bst.Insert(300);
	bst.Insert(100);
	bst.Insert(50);
	bst.Insert(200);
	bst.Insert(500);
	bst.Insert(400);
	bst.Insert(25);
	bst.Insert(75);

	std::printf("\n[Find]\n");
	Node* find = bst.Find(100);
	std::printf("%-20s : Node: %-5p | InValue: %-5d\n", "Find_Result", find, find ? find->Value : -1);
	
	Node* largest = bst.FindLargest();
	std::printf("%-20s : Node: %-5p | InValue: %-5d\n", "FindLargest_Result", largest, largest ? largest->Value : -1);
	
	Node* smallest = bst.FindSmallest();
	std::printf("%-20s : Node: %-5p | InValue: %-5d\n", "FindSmallest_Result", smallest, largest ? smallest->Value : -1);

	std::printf("\n[Erase_0]\n");
	int inValue_erase0 = 50;
	bool erase_0 = bst.Erase(inValue_erase0);
	std::printf("%-20s : InValue: %-5d | Result: %-5s\n", "Erase_Result", inValue_erase0, erase_0 ? "Erase" : "NotErase");
	
	std::printf("\n[Erase_1]\n");
	int inValue_erase1 = 300;
	bool erase_1 = bst.Erase(inValue_erase1);
	std::printf("%-20s : InValue: %-5d | Result: %-5s\n", "Erase_Result", inValue_erase1, erase_1 ? "Erase" : "NotErase");
	
	std::printf("\n[Find_0]\n");
	int inValue_find0 = 50;
	Node* find_0 = bst.Find(inValue_find0);
	std::printf("%-20s : InValue: %-5d | Node: %-5p | Result: %-5s\n", "Find_Result", inValue_find0, find_0, find_0 ? "Found" : "NotFound");
	
	std::printf("\n[Find_1]\n");
	int inValue_find1 = 300;
	Node* find_1 = bst.Find(inValue_find1);
	std::printf("%-20s : InValue: %-5d | Node: %-5p | Result: %-5s\n", "Find_Result", inValue_find1, find_1, find_1 ? "Found" : "NotFound");

	std::printf("\n[TraversePreOrder]\n");
	bst.TraversePreOrder();
	
	std::printf("\n[TraverseInOrder]\n");
	bst.TraverseInOrder();

	std::printf("\n[TraversePostOrder]\n");
	bst.TraversePostOrder();

	std::printf("\n[Clear]\n");
	bst.Clear();

	return 0;
}