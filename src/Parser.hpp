#pragma once
//std
#include <list>

//compiler
#include "Scanner.hpp"

namespace compiler {
	enum class InstType {
		Halt = 0,
		
		NativeCall, FunctionCall, Return, EnterFrame, ReleaseFrame,
		Jump, JumpIf, JumpIfElse,
		Malloc, Realloc, Free,

		Mov, Push, Pop,
		Get, Set, Cmp, 
		Binary
	};

	class Parser {
	public:
		int parse(std::list <token_t>&& tokens);

	private:
		std::list <token_t> _tokens;
	};
}
