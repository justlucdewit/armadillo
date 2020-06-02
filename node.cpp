#include "node.h"

Node::Node(Token tok) {
	this->tok = tok;
}

void Node::print(unsigned int indent = 0) {
	for (unsigned int i = 0; i < indent; i++) {
		std::cout << "  ";
	}

	tok.print();

	if (left != nullptr)
		left->print(indent + 1);

	if (right != nullptr)
		right->print(indent + 1);
}

Node::~Node() {
	if (left != nullptr)
		delete left;

	if (right != nullptr)
		delete right;
}