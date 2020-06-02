#include "lexer.h"

void Lexer::advance() {
	current = code[position++];
}

Token Lexer::makeNumber() {
	std::string number;
	bool isFloat = false;
	while (isdigit(current) || current == '.') {
		if (current == '.') {
			if (isFloat) {
				break;
			}
			isFloat = true;
		}
		number += current;
		advance();
		if (position > code.size()) {
			break;
		}
	}

	position--;

	TokenType tt;
	if (isFloat)
		tt = TokenType::Float;
	else
		tt = TokenType::Integer;

	return Token(tt, number, lineNumber);
}

Token Lexer::nextToken() {
	advance();
	if (position > code.size()) {
		return Token(TokenType::END, "", lineNumber);
	}

	if (current == ' ' || current == '\n' || current == '\t') {
		if (current == '\n') {
			lineNumber++;
		}

		if (position < code.size()) {
			return nextToken();
		}
		else {
			return Token(TokenType::END, "", lineNumber);
		}
	}

	else if (isdigit(current)) {
		return makeNumber();
	}

	else if (current == '+')
		return Token(TokenType::Plus, { current }, lineNumber);

	else if (current == '-')
		return Token(TokenType::Minus, { current }, lineNumber);

	else if (current == '/')
		return Token(TokenType::Divide, { current }, lineNumber);

	else if (current == '*')
		return Token(TokenType::Multiply, { current }, lineNumber);

	else if (current == '^')
		return Token(TokenType::Power, { current }, lineNumber);

	else if (current == '(')
		return Token(TokenType::LeftParen, { current }, lineNumber);

	else if (current == ')')
		return Token(TokenType::RightParen, { current }, lineNumber);

	return Token(TokenType::Unknown, { current }, lineNumber);
}

void Lexer::setCode(std::string code) {
	position = 0;
	this->code = code;
}

std::vector<Token> Lexer::lex() {
	if (code.size() == 0) {
		return {};
	}

	std::vector<Token> tokens;
	Token currentToken = nextToken();
	while (currentToken.type != TokenType::END) {
		tokens.push_back(currentToken);
		currentToken = nextToken();
	}

	return tokens;
}