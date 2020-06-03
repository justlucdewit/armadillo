#include "node.h"

Node::Node(Token tok) {
	this->tok = tok;
}

void Node::print(unsigned int indent) {
	for (unsigned int i = 0; i < indent; i++) {
		std::cout << "  ";
	}

	tok.print();

	if (left != nullptr)
		left->print(indent + 1);

	if (right != nullptr)
		right->print(indent + 1);
}

unsigned int Node::ChildCount() {
	if (this == nullptr)
		return 0;

	unsigned int count = 0;
	if (right == nullptr)
		count++;
	if (left == nullptr)
		count++;
	return count;
}

Node::~Node() {
	if (left != nullptr)
		delete left;

	if (right != nullptr)
		delete right;
}