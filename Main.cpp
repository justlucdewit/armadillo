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

		std::string representation = "Token[";
		representation += ttype;
		representation += ", ";
		representation += value;
		representation += "]\n";
		std::cout << representation;
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

class Node {
public:
	Token tok;
	Node* left = nullptr;
	Node* right = nullptr;

	Node() = default;
	Node(Token tok) {
		this->tok = tok;
	}

	void print(unsigned int indent = 0) {
		for (unsigned int i = 0; i < indent; i++) {
			std::cout << "  ";
		}

		tok.print();

		if (left != nullptr)
			left->print(indent + 1);
		
		if (right != nullptr)
			right->print(indent + 1);
	}

	~Node() {
		if (left != nullptr)
			delete left;

		if (right != nullptr)
			delete right;
	}
};

/*
abstract syntax tree parser
-------------------------------------------
this will beable to parse an set of tokens
into a syntax node tree with the nodes
defined above
*/
class Parser {
private:
	std::vector<Token> tokens;
	unsigned int tokenIndex = 0;
	Token currentToken;
	void advance() {
		if (tokenIndex < tokens.size())
			currentToken = tokens[tokenIndex++];
		else {
			Token t = Token();
			t.type = TokenType::END;
			currentToken = t;
		}
	}

	void revert() {
		if (tokenIndex > 0) {
			tokenIndex -= 1;
			currentToken = tokens[tokenIndex];
		}
	}

	Node* parseNumberLitteral() {
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

	Node* parseTerm() {
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

	Node* parseExpression() {
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

public:
	bool error = false;

	Node* parse(void) {
		return parseExpression();
	}

	void setTokens(std::vector<Token> tokens) {
		this->tokens = tokens;
		tokenIndex = 0;
		error = false;
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

		if (code == "") {
			std::cout << "\n";
			continue;
		}

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

		/*if (!error) {
			for (unsigned int i = 0; i < tokens.size(); i++) {
				tokens[i].print();
			}
		}*/

		parser.setTokens(tokens);
		Node* AST = parser.parse();

		if (parser.error)
			continue;

		AST->print();

		delete AST;
		std::cout << "\n";
	}
}

int main() {
	repl();
}