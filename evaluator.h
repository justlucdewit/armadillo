#include "node.h"

#pragma once
class Evaluator {
private:
	Node* AST;
	void ASTUnaryMinus(Node* SubAST);
	void ASTUnaryPlus(Node* SubAST);

public:
	void setAST(Node* AST);
	void evaluate();
};

