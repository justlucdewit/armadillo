#pragma once

#include <vector>

#include "tokens.h"
#include "node.h"

class Parser {
private:
	std::vector<Token> tokens;
	unsigned int tokenIndex = 0;
	Token currentToken;

	void advance();
	void revert();
	Token peek(int amount = 1);

	Node* parseNumberLitteral();
	Node* parseTerm();
	Node* parseExpression();
	Node* parseExponent();

public:
	bool error = false;

	Node* parse();

	void setTokens(std::vector<Token> tokens);
};