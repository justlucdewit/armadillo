#pragma once
#include <vector>
#include <string>

#include "tokens.h"

class Lexer {
private:
	std::string code;
	unsigned int position = 0;
	unsigned int lineNumber = 1;
	char current = '\0';

	void advance();
	Token makeNumber();
	Token nextToken();

public:
	void setCode(std::string code);

	std::vector<Token> lex();
};