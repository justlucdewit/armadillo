#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "tokens.h"
#include "lexer.h"
#include "node.h"
#include "parser.h"
#include "evaluator.h"

void repl() {
	std::cout << "Dilly V1.0.0\n\n";
	Lexer lexer;
	Parser parser;
	Evaluator evalueator;

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

		// error handling
		bool error = false;
		for (unsigned int i = 0; i < tokens.size(); i++) {
			if (tokens[i].type == TokenType::Unknown) {
				error = true;
				std::cout << "[ERROR] unknown token: '" << tokens[i].value << "' on line " << tokens[i].lineNumber <<"\n";
			}
		}

		if (error)
			continue;

		// parsing the tokens to an AST
		parser.setTokens(tokens);
		Node* AST = parser.parse();

		if (parser.error)
			continue;

		AST->print();

		// evaluate expression
		evalueator.setAST(AST);
		evalueator.evaluate();

		std::cout << "---------------\n";
		AST->print();
		//std::cout << AST->tok.value << "\n";


		// clean up
		delete AST;
		std::cout << "\n";
	}
}

int main() {
	repl();
}