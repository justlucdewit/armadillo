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

void Evaluator::ASTAdd(Node* SubAST) {
	std::string lval = SubAST->left->tok.value;
	std::string rval = SubAST->right->tok.value;
	TokenType ltype = SubAST->left->tok.type;
	TokenType rtype = SubAST->right->tok.type;
	delete SubAST->left;
	delete SubAST->right;
	SubAST->left = nullptr;
	SubAST->right = nullptr;

	if (ltype == TokenType::Float) {
		if (rtype != TokenType::Float) {
			std::cout << "[ERROR] implicite typecast from Float to Integer on line " << SubAST->tok.lineNumber << "\n\n";
			error = true;
			return;
		}
		SubAST->tok.type = TokenType::Float;
		SubAST->tok.value = std::to_string(std::stof(lval) + std::stof(rval));
		
	}

	else {
		if (rtype != TokenType::Integer) {
			std::cout << "[ERROR] implicite typecast from Integer to Float on line " << SubAST->tok.lineNumber << "\n\n";
			error = true;
			return;
		}
		SubAST->tok.type = TokenType::Integer;
		SubAST->tok.value = std::to_string(std::stoi(lval) + std::stoi(rval));
	}
}

void Evaluator::ASTSubtract(Node* SubAST) {
	std::string lval = SubAST->left->tok.value;
	std::string rval = SubAST->right->tok.value;
	TokenType ltype = SubAST->left->tok.type;
	TokenType rtype = SubAST->right->tok.type;
	delete SubAST->left;
	delete SubAST->right;
	SubAST->left = nullptr;
	SubAST->right = nullptr;

	if (ltype == TokenType::Float) {
		if (rtype != TokenType::Float) {
			std::cout << "[ERROR] implicite typecast from Float to Integer on line " << SubAST->tok.lineNumber << "\n\n";
			error = true;
			return;
		}
		SubAST->tok.type = TokenType::Float;
		SubAST->tok.value = std::to_string(std::stof(lval) - std::stof(rval));// ! problem here

	}

	else {
		if (rtype != TokenType::Integer) {
			std::cout << "[ERROR] implicite typecast from Integer to Float on line " << SubAST->tok.lineNumber << "\n\n";
			error = true;
			return;
		}
		SubAST->tok.type = TokenType::Integer;
		SubAST->tok.value = std::to_string(std::stoi(lval) - std::stoi(rval));// ! problem here
	}
}

void Evaluator::ASTMultiply(Node* SubAST) {
	std::string lval = SubAST->left->tok.value;
	std::string rval = SubAST->right->tok.value;
	TokenType ltype = SubAST->left->tok.type;
	TokenType rtype = SubAST->right->tok.type;
	delete SubAST->left;
	delete SubAST->right;
	SubAST->left = nullptr;
	SubAST->right = nullptr;

	if (ltype == TokenType::Float) {
		if (rtype != TokenType::Float) {
			std::cout << "[ERROR] implicite typecast from Float to Integer on line " << SubAST->tok.lineNumber << "\n\n";
			error = true;
			return;
		}
		SubAST->tok.type = TokenType::Float;
		SubAST->tok.value = std::to_string(std::stof(lval) * std::stof(rval));

	}

	

	else {
		if (rtype != TokenType::Integer) {
			std::cout << "[ERROR] implicite typecast from Integer to Float on line " << SubAST->tok.lineNumber << "\n\n";
			error = true;
			return;
		}
		SubAST->tok.type = TokenType::Integer;
		SubAST->tok.value = std::to_string(std::stoi(lval) * std::stoi(rval));
	}
}

void Evaluator::ASTDivide(Node* SubAST) {
	std::string lval = SubAST->left->tok.value;
	std::string rval = SubAST->right->tok.value;
	TokenType ltype = SubAST->left->tok.type;
	TokenType rtype = SubAST->right->tok.type;
	delete SubAST->left;
	delete SubAST->right;
	SubAST->left = nullptr;
	SubAST->right = nullptr;

	if (ltype == TokenType::Float) {
		if (rtype != TokenType::Float) {
			std::cout << "[ERROR] implicite typecast from Float to Integer on line " << SubAST->tok.lineNumber << "\n\n";
			error = true;
			return;
		}
		SubAST->tok.type = TokenType::Float;
		SubAST->tok.value = std::to_string(std::stof(lval) / std::stof(rval));

	}

	else {
		if (rtype != TokenType::Integer) {
			std::cout << "[ERROR] implicite typecast from Integer to Float on line " << SubAST->tok.lineNumber << "\n\n";
			error = true;
			return;
		}
		SubAST->tok.type = TokenType::Integer;

		if (std::stoi(rval) == 0) {
			std::cout << "[ERROR] division by 0 on line " << SubAST->tok.lineNumber << "\n\n";
			error = true;
			return;
		}

		SubAST->tok.value = std::to_string(std::stoi(lval) / std::stoi(rval));
	}
}

void Evaluator::ASTExponent(Node* SubAST) {
	std::string lval = SubAST->left->tok.value;
	std::string rval = SubAST->right->tok.value;
	TokenType ltype = SubAST->left->tok.type;
	TokenType rtype = SubAST->right->tok.type;
	delete SubAST->left;
	delete SubAST->right;
	SubAST->left = nullptr;
	SubAST->right = nullptr;

	if (ltype == TokenType::Float) {
		if (rtype != TokenType::Float) {
			std::cout << "[ERROR] implicite typecast from Float to Integer on line " << SubAST->tok.lineNumber << "\n\n";
			error = true;
			return;
		}
		SubAST->tok.type = TokenType::Float;
		SubAST->tok.value = std::to_string(std::pow(std::stof(lval), std::stof(rval)));

	}

	else {
		if (rtype != TokenType::Integer) {
			std::cout << "[ERROR] implicite typecast from Integer to Float on line " << SubAST->tok.lineNumber << "\n\n";
			error = true;
			return;
		}
		SubAST->tok.type = TokenType::Integer;

		if (std::stoi(rval) == 0) {
			std::cout << "[ERROR] division by 0 on line " << SubAST->tok.lineNumber << "\n\n";
			error = true;
			return;
		}

		SubAST->tok.value = std::to_string((int) std::pow(std::stoi(lval), std::stoi(rval)));
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
	if (AST->left != nullptr && AST->right != nullptr && AST->left->left == nullptr && AST->left->right == nullptr && AST->right->left == nullptr && AST->right->right == nullptr) {
		switch (AST->tok.type) {
		case TokenType::Plus:
			ASTAdd(AST);
			return;
		case TokenType::Minus:
			ASTSubtract(AST);
			return;
		case TokenType::Divide:
			ASTDivide(AST);
			return;
		case TokenType::Multiply:
			ASTMultiply(AST);
			return;
		case TokenType::Power:
			ASTExponent(AST);
			return;
		}
	}
}