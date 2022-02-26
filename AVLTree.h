#pragma once
#include <string>
#include "Node.h"

class AVLTree
{
public:
	AVLTree();
	~AVLTree();

	void Insert(int data);
	void Print();
	void PreOrderTraversal();
	void SearchHelper(Node* cursor);
	void Remove(int target);

private:
	Node* root;

	void DestructorHelper(Node* cursor);
	Node* InsertHelper(Node* cursor, int data);
	void PrintHelper(Node* cursor, std::string indent);
	void SearchHelper(Node* cursor, int target);
	Node* RemoveHelper(Node* cursor, int target);
	bool IsLeaf(Node* cursor);
	Node* FindSuccessor(Node* cursor);
	int UpdateHeight(Node* cursor);
	int UpdateBalance(Node* cursor);
	Node* RebalanceIfNeeded(Node* cursor);
	Node* RightRotate(Node* cursor);

	Node* LeftRotate(Node* cursor);

	Node* RightLeft(Node* cursor);

	Node* LeftRight(Node* cursor);
};