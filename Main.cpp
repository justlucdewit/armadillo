#include <iostream>
#include <string>
#include <vector>
#include <memory>

/*
Lexical analyzer
-------------------------------------------
analyze the lexical components of the code,
and chop it into atoms named Tokens
*/
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
	END
};

class Token {
public:
	TokenType type;
	std::string value;
	unsigned int lineNumber;

	Token() = default;

	Token(TokenType type, std::string value, unsigned int lineNumber) {
		this->type = type;
		this->value = value;
		this->lineNumber = lineNumber;
	}
	
	void print(void) {
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
		case TokenType::END:
			ttype = "End";
			break;
		default:
			ttype = "Unknown";
		}
		std::cout << "Token[" << ttype << ", " << value << "]\n";
	}
};

class Lexer {
private:
	std::string code;
	unsigned int position = 0;
	unsigned int lineNumber = 1;
	char current = '\0';

	void advance(void) {
		current = code[position++];
	}

	Token makeNumber() {
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

	Token nextToken(void) {
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

public:
	void setCode(std::string code) {
		position = 0;
		this->code = code;
	};

	

	std::vector<Token> lex(void) {
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
};

/*
abstract syntax nodes
-------------------------------------------
nodes that will be used to build the
abstract syntax tree
*/

class Expression {
	virtual void eval() = 0;
};

class NumberLitteral: public Expression {
public:
	Token token;
	NumberLitteral() = default;
	NumberLitteral(Token token) {
		this->token = token;
	}

	void eval() {
		return;// token;
	}
};

class BinaryOpperation : public Expression {
public:
	Token op;
	std::unique_ptr<Expression> left;
	std::unique_ptr<Expression> right;

	/*Token*/ void eval() {
		if (op.type == TokenType::Multiply) {
			//multiply left and right token and return the new token
		}
		//return a token of type unknown
	}
};

class Parser {
private:
	std::vector<Token> tokens;
	unsigned int tokenIndex = 0;
	Token currentToken;
	void advance() {
		if (tokenIndex < tokens.size())
			currentToken = tokens[tokenIndex++];
	}

	NumberLitteral parseNumberLitteral() {
		advance();
		if (currentToken.type == TokenType::Integer || currentToken.type == TokenType::Float) {
			return NumberLitteral(currentToken);
		}
	}

	void parseTerm() {
		BinaryOpperation left;
		left.left = parseNumberLitteral();

		advance();
		while (currentToken.type == TokenType::Multiply || currentToken.type == TokenType::Divide) {
			Token op = currentToken;
			NumberLitteral right = parseNumberLitteral();
		}
	}

public:
	void parse(void) {

	}

	void setTokens(std::vector<Token> tokens) {
		this->tokens = tokens;
		tokenIndex = 0;
	}
};

void repl() {
	std::cout << "Dilly V1.0.0\n\n";
	Lexer lexer;
	Parser parser;
	while (true) {
		std::string code;
		std::cout << ">> ";
		std::getline(std::cin, code);

		// do lexing
		lexer.setCode(code);
		std::vector<Token> tokens = lexer.lex();

		bool error = false;
		for (unsigned int i = 0; i < tokens.size(); i++) {
			if (tokens[i].type == TokenType::Unknown) {
				error = true;
				std::cout << "[ERROR] unknown token: '" << tokens[i].value << "' on line " << tokens[i].lineNumber <<"\n";
			}
		}

		if (!error) {
			for (unsigned int i = 0; i < tokens.size(); i++) {
				tokens[i].print();
			}
		}

		parser.setTokens(tokens);
		parser.parse();

		std::cout << "\n";
	}
}

int main() {
	repl();
}