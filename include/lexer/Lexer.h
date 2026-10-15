
#pragma once

#include "lexer/Token.h"

#include <cstddef>
#include <string>

namespace lexer {

class Lexer {
public:
    explicit Lexer(std::string source);

    Token nextToken();

private:
    std::string source_;

    std::size_t position_ = 0;
    std::size_t line_ = 1;
    std::size_t column_ = 1;

    bool isAtEnd() const;

    char peek() const;
    char peekNext() const;

    char advance();

    void skipWhitespace();

    static bool isIdentifierStart(char c);
    static bool isIdentifierContinue(char c);

    Token identifierOrKeyword(
        std::size_t start,
        std::size_t startLine,
        std::size_t startColumn
    );
};

} // namespace lexer