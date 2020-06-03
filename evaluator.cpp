#include "evaluator.h"

void Evaluator::setAST(Node* AST) {
	this->AST = AST;
}

void Evaluator::ASTUnaryMinus(Node* SubAST) {
	SubAST->tok = SubAST->left->tok;
	delete SubAST->left;
	SubAST->left = nullptr;

	if (SubAST->tok.value[0] == '-') {
		SubAST->tok.value.erase(SubAST->tok.value.begin());
	}
	else {
		SubAST->tok.value = "-" + SubAST->tok.value;
	}
}

void Evaluator::ASTUnaryPlus(Node* SubAST) {
	SubAST->tok = SubAST->left->tok;
	delete SubAST->left;
	SubAST->left = nullptr;

	if (SubAST->tok.value[0] == '-') {
		SubAST->tok.value.erase(SubAST->tok.value.begin());
	}
}

void Evaluator::evaluate() {
	Evaluator evaluator;

	if (AST->left != nullptr) {
		evaluator.setAST(AST->left);
		evaluator.evaluate();
	}

	if (AST->right != nullptr) {
		evaluator.setAST(AST->right);
		evaluator.evaluate();
	}

	// unary operators
	if (AST->left != nullptr && AST->left->right == nullptr && AST->left->left == nullptr) {
		switch (AST->tok.type) {
		case TokenType::UnaryPlus:
			ASTUnaryPlus(AST);
			return;
		case TokenType::UnaryMinus:
			ASTUnaryMinus(AST);
			return;
		}
	}

	// binary operators
}