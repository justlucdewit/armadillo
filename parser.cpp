#include "parser.h"

void Parser::advance() {
	if (tokenIndex < tokens.size())
		currentToken = tokens[tokenIndex++];
	else {
		Token t = Token();
		t.type = TokenType::END;
		currentToken = t;
	}
}

void Parser::revert() {
	if (tokenIndex > 0) {
		tokenIndex -= 1;
		currentToken = tokens[tokenIndex];
	}
}

Node* Parser::parseNumberLitteral() {
	advance();
	if (currentToken.type == TokenType::Integer || currentToken.type == TokenType::Float) {
		return new Node(currentToken);
	}

	else if (currentToken.type == TokenType::Plus || currentToken.type == TokenType::Minus) {
		Token old = currentToken;
		Node* factor = parseNumberLitteral();
		Node* ret = new Node();

		if (old.type == TokenType::Plus)
			ret->tok = Token(TokenType::UnaryPlus, "+", old.lineNumber);
		else
			ret->tok = Token(TokenType::UnaryMinus, "-", old.lineNumber);

		ret->left = factor;

		return ret;
	}

	else if (currentToken.type == TokenType::LeftParen) {
		std::vector<Token> subexprTokens;

		// load sub expression
		advance();
		unsigned int parenCount = 1;

		if (currentToken.type == TokenType::RightParen) {
			std::cout << "syntax error, expected a number litteral, got: ";
			currentToken.print();
			error = true;
		}

		while (parenCount != 0) {
			if (currentToken.type == TokenType::END) {
				std::cout << "syntax error, expected a ) but found end of file";
				error = true;
				break;
			}

			if (currentToken.type == TokenType::LeftParen)
				parenCount++;

			if (currentToken.type == TokenType::RightParen)
				parenCount--;

			subexprTokens.push_back(currentToken);

			advance();
		}

		subexprTokens.pop_back();

		Parser subexprParser;
		subexprParser.setTokens(subexprTokens);
		Node* subAST = subexprParser.parse();

		error = subexprParser.error;

		revert();

		return subAST;
	}

	else {
		std::cout << "syntax error, expected a number litteral, got: ";
		currentToken.print();
		error = true;

		return new Node();
	}
}

Node* Parser::parseTerm() {
	Node* root = new Node();
	root->left = parseNumberLitteral();

	advance();

	while (currentToken.type == TokenType::Multiply || currentToken.type == TokenType::Divide) {
		Token op = currentToken;
		Node* right = parseNumberLitteral();

		Node* newRoot = new Node();
		root->right = right;
		root->tok = op;
		newRoot->left = root;
		root = newRoot;
		advance();
	}

	return root->left;
}

Node* Parser::parseExpression() {
	Node* root = new Node();
	root->left = parseTerm();

	// advance();

	while (currentToken.type == TokenType::Plus || currentToken.type == TokenType::Minus) {
		Token op = currentToken;
		Node* right = parseTerm();
		// std::cout << right->left->tok.print();

		Node* newRoot = new Node();
		root->right = right;
		root->tok = op;
		newRoot->left = root;
		root = newRoot;
	}

	return root->left;
}

Node* Parser::parse() {
	return parseExpression();
}

void Parser::setTokens(std::vector<Token> tokens) {
	this->tokens = tokens;
	tokenIndex = 0;
	error = false;
}