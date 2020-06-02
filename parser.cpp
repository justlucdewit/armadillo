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