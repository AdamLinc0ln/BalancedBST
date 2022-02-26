#pragma once
class Node
{
public:
	Node();
	Node(int data);
	~Node();

	int data;
	Node* left;
	Node* right;
	int height;//height = max of left or right childs height +1 //no child =-1
	int balance;//balance factor? = left child height - right child height // no child = -1
};
