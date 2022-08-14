#include "Scanner.hpp"

namespace compiler {
	std::string to_string(TokenType type) {
		using enum TokenType;

		switch (type) {
		case None: return "None";

		case LeftParen: return "LeftParen";
		case RightParen: return "RightParen";
		case LeftBracket: return "LeftBrace";
		case RightBracket: return "RightBrace";

		case Comma: return "Comma";
		case Dot: return "Dot";
		case Minus: return "Minus";
		case Plus: return "Plus";
		case Colon: return "Colon";
		case Semicolon: return "Semicolon";
		case Slash: return "Slash";

		case Percent: return "Percent";
		case Dollar: return "Dollar";

		case String: return "String";
		case Hex: return "Hex";
		case Number: return "Number";
		case Identifier: return "Identifier"; break;
		case Comment: return "Comment";

		case EndOfFile: return "EOF";

		default: return "None";
		}
	}
	std::string to_string(token_t token) {
		return to_string(token.type) + ' ' + token.lexeme + ' ' + std::to_string(token.line);
	}

	token_t::token_t(TokenType type, std::string lexeme, size_t line) : 
		type(type), 
		lexeme(lexeme), 
		line(line) {
	}

	//Scanner

	int Scanner::scan(std::istream& in) {
		std::string code(std::istreambuf_iterator <char>(in), {});
		_source = std::move(code);

		while (!_IsEnd()) {
			_start = _current;
			_ScanToken();
		}

		_AddToken(TokenType::EndOfFile);

		return 0;
	}

	std::list<token_t>& Scanner::tokens() {
		return _tokens;
	}

	bool Scanner::_IsEnd() {
		return _current >= _source.size();
	}
	char Scanner::_Advance() {
		return _source[_current++];
	}

	bool Scanner::_IsNext(char expected) {
		if (_IsEnd() || _source[_current] != expected)
			return false;

		_current++;
		return true;
	}
	char Scanner::_Peek() {
		if (_IsEnd())
			return '\0';
		return _source[_current];
	}
	char Scanner::_PeekNext() {
		if (_current + 1 >= _source.size()) return '\0';
		return _source[_current + 1];
	}

	bool Scanner::_IsDigit(char what) {
		return what >= '0' && what <= '9';
	}
	bool Scanner::_IsAlpha(char what) {
		return (what >= 'a' && what <= 'z') || (what >= 'A' && what <= 'Z') || what == '_';
	}
	bool Scanner::_IsAlphaNumeric(char what) {
		return _IsAlpha(what) || _IsDigit(what);
	}

	void Scanner::_ScanToken() {
		using enum TokenType;

		char c = _Advance();
		switch (c) {
		case '(': _AddToken(LeftParen); break;
		case ')': _AddToken(RightParen); break;
		case '[': _AddToken(LeftBracket); break;
		case ']': _AddToken(RightBracket); break;

		case ',': _AddToken(Comma); break;
		case '.': _AddToken(Dot); break;
		case '-': _AddToken(Minus); break;
		case '+': _AddToken(Plus); break;
		case ':': _AddToken(Colon); break;
		case ';': _AddToken(Semicolon); break;
		case '/':
			if (_IsNext('/')) {
				while (_Peek() != '\n' && !_IsEnd())
					_Advance();
				_AddToken(Comment);
			} else {
				_AddToken(Slash);
			}
			break;
		case '%': _AddToken(Percent); break;
		case '$': _AddToken(Dollar); break;

		case ' ':
		case '\t':
		case '\r':
			//just ignore them
			break;

		case '\n': _line++; break;

		default:
			if (_IsDigit(c)) {
				_ScanNumber();
			} else if (_IsAlpha(c)) {
				_ScanIdentifier();
			} else {
				//TODO: throw error
			}
		}
	}
	void Scanner::_ScanString() {
		while (_Peek() != '\"' && _IsEnd()) {
			if (_Peek() == '\n')
				_line++;
			_Advance();
		}

		if (_IsEnd()) {
			//TODO: throw exception about "Unterminated string"
		}

		//Closing "
		_Advance();

		_AddToken(TokenType::String);
	}
	//TODO: create 
	void Scanner::_ScanNumber() {
		while (_IsDigit(_Peek())) _Advance();

		if (_Peek() == 'h') {
			_Advance();
			_AddToken(TokenType::Hex);
		} else {
			_AddToken(TokenType::Number);
		}
	}
	void Scanner::_ScanIdentifier() {
		while (_IsAlphaNumeric(_Peek())) 
			_Advance();

		_AddToken(TokenType::Identifier);
	}

	void Scanner::_AddToken(TokenType type) {
		std::string text = _source.substr(_start, _current - _start);
		_tokens.push_back(token_t(type, text, _line));
	}
}