#include "Parser.hpp"

#include <unordered_set>

namespace compiler {
	using TokenIt = std::list <token_t>::iterator;

	InstType match_identifier(const std::string& lexeme) {
		using enum InstType;
		static const std::unordered_set <std::string> altas = {

		};

		if (lexeme == "halt") {
			return Halt;
		} else if (lexeme == "ncall") {
			return NativeCall;
		} else if (lexeme == "fcall") {
			return FunctionCall;
		} else if (lexeme == "ret") {
			return Return;
		} else if (lexeme == "enter") {
			return EnterFrame;
		} else if (lexeme == "release") {
			return ReleaseFrame;
		} else if (lexeme == "malloc") {
			return Malloc;
		} else if (lexeme == "realloc") {
			return Realloc;
		} else if (lexeme == "free") {
			return Free;
		} else if (lexeme.starts_with("mov")) {
			return Mov;
		} else if (lexeme.starts_with("push")) {
			return Push;
		} else if (lexeme.starts_with("pop")) {
			return Pop;
		} else if (lexeme.starts_with("get")) {
			return Get;
		} else if (lexeme.starts_with("set")) {
			return Set;
		} else {

		}
	}

	namespace pattern {
		bool __halt_match(TokenIt it) {

		}
	}

	int Parser::parse(std::list <token_t>&& tokens) {
		_tokens = std::move(tokens);
		


		return 0;
	}
}
