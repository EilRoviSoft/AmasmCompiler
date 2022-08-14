//std
#include <iostream>
#include <fstream>

//compiler
#include "src/Scanner.hpp"

int main() {
    compiler::Scanner scanner;

    std::ifstream file("asm/test.asm");

    int err = scanner.scan(file);

    file.close();

    for (const auto& it : scanner.tokens()) {
        std::cout << compiler::to_string(it) << '\n';
    }

    return 0;
}