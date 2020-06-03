#pragma once
#include <iostream>

#include "tokens.h"

class Node {
public:
	Token tok;
	Node* left = nullptr;
	Node* right = nullptr;

	Node() = default;
	Node(Token tok);

	void print(unsigned int indent = 0);
	unsigned int ChildCount();

	~Node();
};
