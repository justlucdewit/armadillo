#include "node.h"

#pragma once
class Evaluator {
private:
	Node* AST;
	void ASTUnaryMinus(Node* SubAST);
	void ASTUnaryPlus(Node* SubAST);

	void ASTSubtract(Node* SubAST);
	void ASTAdd(Node* SubAST);
	void ASTMultiply(Node* SubAST);
	void ASTDivide(Node* SubAST);

public:
	bool error = false;
	void setAST(Node* AST);
	void evaluate();
};

