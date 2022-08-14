#include "Parser.hpp"

namespace compiler {
	int Parser::parse(std::list<token_t>&& tokens) {
		_tokens = std::move(tokens);
		
		return 0;
	}
}