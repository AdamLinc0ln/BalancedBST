#include "Node.h"

Node::Node()
{
	left = right = nullptr;
}

Node::Node(int data)
{
	left = right = nullptr;
	this->data = data;
	height = 0;
}

Node::~Node()
{
}

