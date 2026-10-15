
#include "lexer/Lexer.h"
#include "lexer/Token.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

namespace {

void printToken(const lexer::Token& token) {
    std::cout
        << lexer::tokenKindName(token.kind)
        << "\t\"" << token.lexeme << "\""
        << "\t" << token.line << ":" << token.column
        << '\n';
}

} // namespace

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: minic <source-file>\n";
        return 1;
    }

    const std::string filename = argv[1];

    std::ifstream input(filename);

    if (!input) {
        std::cerr << "Error: cannot open source file: "
                  << filename << '\n';
        return 1;
    }

    std::string source{
        std::istreambuf_iterator<char>(input),
        std::istreambuf_iterator<char>()
    };

    lexer::Lexer lexer(std::move(source));

    while (true) {
        lexer::Token token = lexer.nextToken();
        printToken(token);

        if (token.kind == lexer::TokenKind::EndOfFile) {
            break;
        }
    }

    return 0;
}