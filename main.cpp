//std
#include <iostream>
#include <fstream>

//compiler
#include "src/Scanner.hpp"
#include "src/Parser.hpp"

int main() {
	compiler::Scanner scanner;
	compiler::Parser parser;

	//Scanning code

	std::ifstream file("asm/test.asm");
	auto tokens = scanner.scan(file);
	//auto tokens = scanner.release();
	file.close();

	for (const auto& it : tokens) {
		std::cout << compiler::to_string(it) << '\n';
	}

	//Parsing code

	parser.parse(std::move(tokens));

	return 0;
}