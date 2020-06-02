#pragma once
#include <iostream>
#include <string>

enum class TokenType {
	Integer,
	Float,
	Plus,
	Minus,
	Divide,
	Multiply,
	Power,
	Keyword,
	LeftParen,
	RightParen,
	Unknown,
	END,
	UnaryPlus,
	UnaryMinus,
};

class Token {
public:
	TokenType type = TokenType::Unknown;
	std::string value;
	unsigned int lineNumber = 0;

	Token() = default;
	Token(TokenType type, std::string value, unsigned int lineNumber);

	void print();
};