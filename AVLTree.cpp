#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "AVLTree.h"

using namespace std;



AVLTree::AVLTree()
{
	root = nullptr;
}


AVLTree::~AVLTree()
{
	DestructorHelper(root);
}
void AVLTree::DestructorHelper(Node* cursor)
{
	// base case
	if (cursor == nullptr)
		return;

	// delete left
	DestructorHelper(cursor->left);
	// delete right
	DestructorHelper(cursor->right);
	// delete me
	delete cursor;
}

void AVLTree::Insert(int data)
{
	root = InsertHelper(root, data);
}
Node* AVLTree::InsertHelper(Node* cursor, int data)
{
	// base case
	if (cursor == nullptr)
		return new Node(data);

	if (data <= cursor->data)
		cursor->left = InsertHelper(cursor->left, data);
	else
		cursor->right = InsertHelper(cursor->right, data);

	//update height
	cursor->height = UpdateHeight(cursor);
	cursor->balance = UpdateBalance(cursor);

	//rotate if needed
	Node* newChild = RebalanceIfNeeded(cursor);
	cursor->height = UpdateHeight(cursor);
	cursor->balance = UpdateBalance(cursor);

	//return cursor;
	return newChild;
}

void AVLTree::Print()
{
	cout << endl;
	PrintHelper(root, "");
	cout << endl;
}
void AVLTree::PrintHelper(Node* cursor, std::string indent)
{
	if (cursor == nullptr)
		cout << indent << "[leaf]" << endl;
	else
	{
		cout << indent << cursor->data << " (" << cursor->height << ")" << endl;
		PrintHelper(cursor->left, indent + "   ");
		PrintHelper(cursor->right, indent + "   ");
	}
}

void AVLTree::PreOrderTraversal()//int target
{
	cout << endl;
	return SearchHelper(root);
}
void AVLTree::SearchHelper(Node* cursor)//print out here void?
{
	// base cases
	if (cursor != nullptr)
	{
		cout << cursor->data << ", ";
		SearchHelper(cursor->left);
		SearchHelper(cursor->right);
		return;
	}
	return;
}

bool AVLTree::IsLeaf(Node* cursor)
{
	if (cursor == nullptr)
		throw invalid_argument("nullptr passed to IsLeaf()");
	if (cursor->left == nullptr && cursor->right == nullptr)
		return true;
	else
		return false;
}

Node* AVLTree::FindSuccessor(Node* cursor)
{
	Node* successor = cursor->right;

	while (successor->left != nullptr)
		successor = successor->left;

	return successor;
}

void AVLTree::Remove(int target)
{
	RemoveHelper(root, target);
}
Node* AVLTree::RemoveHelper(Node* cursor, int target)
{
	// base cases
	if (cursor == nullptr)
		return nullptr;
	if (cursor->data == target)
	{
		// case 2: cursor is a leaf
		if (IsLeaf(cursor))
		{
			delete cursor;
			return nullptr;
		}
		// case 3: cursor has only one child
		else if (cursor->right != nullptr && cursor->left == nullptr)
		{
			Node* tmp = cursor->right;
			delete cursor;
			return tmp;
		}
		else if (cursor->left != nullptr && cursor->right == nullptr)
		{
			Node* tmp = cursor->left;
			delete cursor;
			return tmp;
		}
		else
		{
			// case 4: cursor has both children
			Node* successor = FindSuccessor(cursor);
			cursor->data = successor->data;
			cursor->right = RemoveHelper(cursor->right, successor->data);
			return cursor;
		}
	}
	else
	{
		if (target < cursor->data)
			cursor->left = RemoveHelper(cursor->left, target);
		else
			cursor->right = RemoveHelper(cursor->right, target);

		return cursor;
	}
}

int AVLTree::UpdateHeight(Node* cursor)//return an int?
{
	if (cursor == nullptr)
		return cursor->height = 0;
	//max of left and right height +1

	int leftHeight = -1;
	int rightHeight = -1;

	if (cursor->left != nullptr)
		leftHeight = cursor->left->height;

	if (cursor->right != nullptr)
		rightHeight = cursor->right->height;

	return cursor->height = max(leftHeight, rightHeight) + 1;
}

Node* AVLTree::RightRotate(Node* cursor)//+2 for balance (left-heavy problem)
{
	Node* temp = cursor->left;
	cursor->left = temp->right;
	temp->right = cursor;
	UpdateHeight(cursor);
	UpdateHeight(temp);
	return temp;
}
Node* AVLTree::LeftRotate(Node* cursor)//-2 for balance (Right-Heavy problem) Right right problem
{
	Node* temp = cursor->right;
	cursor->right = temp->left;
	temp->left = cursor;
	UpdateHeight(cursor);
	UpdateHeight(temp);

	return temp;
}
//right left rotation
Node* AVLTree::RightLeft(Node* cursor)//cursor right child has left child 
{
	cursor->right = RightRotate(cursor->right);
	cursor = LeftRotate(cursor);//left rotate returns a temp avl tree but returns cursor so cursor = leftRotate(cursor)
	return cursor;
}
//left right rotation
Node* AVLTree::LeftRight(Node* cursor)//cursor left child has right child
{
	cursor->left = LeftRotate(cursor->left);
	cursor = RightRotate(cursor);
	return cursor;
}
//rebalance
Node* AVLTree::RebalanceIfNeeded(Node* cursor)
{
	//Right Rotate balance = 2 left child balance = 1
	if (cursor->balance == 2 && cursor->left->balance == 1)
	{
		return RightRotate(cursor);
	}
	//Left Rotate balance = -2 right child balance =-1
	if (cursor->balance == -2 && cursor->right->balance == -1)
	{
		return LeftRotate(cursor);
	}
	//Right Left balance =-2 right child balance =1
	if (cursor->balance == -2 && cursor->right->balance == 1)
	{
		return RightLeft(cursor);
	}
	//Left right balance = 2 left child balance =-1
	if (cursor->balance == 2 && cursor->left->balance == -1)
	{
		return LeftRight(cursor);
	}
	return cursor;
}
//update balance
int AVLTree::UpdateBalance(Node* cursor)
{
	if (cursor == nullptr)
		return cursor->balance = 0;
	//max of left and right height +1

	int leftHeight = -1;
	int rightHeight = -1;

	if (cursor->left != nullptr)
		leftHeight = cursor->left->height;

	if (cursor->right != nullptr)
		rightHeight = cursor->right->height;

	return cursor->balance = leftHeight - rightHeight;
}