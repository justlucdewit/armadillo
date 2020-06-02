#include "tokens.h"

Token::Token(TokenType type, std::string value, unsigned int lineNumber) {
	this->type = type;
	this->value = value;
	this->lineNumber = lineNumber;
}

void Token::print() {
	std::string ttype;
	switch (type) {
	case TokenType::Integer:
		ttype = "Integer";
		break;
	case TokenType::Float:
		ttype = "Float";
		break;
	case TokenType::Plus:
		ttype = "Plus";
		break;
	case TokenType::Minus:
		ttype = "Minus";
		break;
	case TokenType::Divide:
		ttype = "Divide";
		break;
	case TokenType::Multiply:
		ttype = "Multiply";
		break;
	case TokenType::Power:
		ttype = "Power";
		break;
	case TokenType::Keyword:
		ttype = "Keyword";
		break;
	case TokenType::LeftParen:
		ttype = "LeftParentesis";
		break;
	case TokenType::RightParen:
		ttype = "RightParentesis";
		break;
	case TokenType::UnaryMinus:
		ttype = "UnaryMinus";
		break;
	case TokenType::UnaryPlus:
		ttype = "UnaryPlus";
		break;
	case TokenType::END:
		ttype = "End";
		break;
	default:
		ttype = "Unknown";
	}

	std::cout << "Token[" << ttype << ", " << value << "]\n";
}