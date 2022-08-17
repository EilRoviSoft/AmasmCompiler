#pragma once
//std
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <list>

//util
#include "Util.hpp"

namespace compiler {
	enum class TokenType {
		None = 0,

		//Single char tokens
		LeftParen, RightParen, LeftBracket, RightBracket,
		Comma, Dot, Minus, Plus, Colon, Semicolon, Slash,
		Percent, Dollar,

		//Literals
		String, Hex, Number, Identifier, Comment,

		EndOfFile
	};
	std::string to_string(TokenType type);

	struct token_t {
		TokenType type;
		std::string lexeme;
		//TODO: literal
		size_t line;

		token_t(TokenType type, std::string lexeme, size_t line);
	};
	std::string to_string(token_t token);

	class Scanner {
	public:
		//throw error as number
		std::list <token_t>&& scan(std::istream& in);

		std::list <token_t>& tokens();

	private:
		std::string _source;
		std::list <token_t> _tokens;
		size_t _start = 0;
		size_t _current = 0;
		size_t _line = 1;

		bool _IsEnd();
		char _Advance();

		bool _IsNext(char expected);
		char _Peek();
		char _PeekNext();

		bool _IsDigit(char what);
		bool _IsAlpha(char what);
		bool _IsAlphaNumeric(char what);

		void _ScanToken();
		void _ScanString();
		void _ScanNumber();
		void _ScanIdentifier();

		void _AddToken(TokenType type);
	};
}
