#pragma once
//std
#include <list>

//compiler
#include "Scanner.hpp"

namespace compiler {
	class Parser {
	public:
		int parse(std::list <token_t>&& tokens);

	private:
		std::list <token_t> _tokens;
	};
}