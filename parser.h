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

	Node* parseNumberLitteral();
	Node* parseTerm();
	Node* parseExpression();

public:
	bool error = false;

	Node* parse();

	void setTokens(std::vector<Token> tokens);
};