
#include "lexer/Lexer.h"

#include <cctype>
#include <string_view>
#include <utility>

namespace lexer {

Lexer::Lexer(std::string source)
    : source_(std::move(source)) {}

bool Lexer::isAtEnd() const {
    return position_ >= source_.size();
}

char Lexer::peek() const {
    if (isAtEnd()) {
        return '\0';
    }

    return source_[position_];
}

char Lexer::peekNext() const {
    if (position_ + 1 >= source_.size()) {
        return '\0';
    }

    return source_[position_ + 1];
}

char Lexer::advance() {
    if (isAtEnd()) {
        return '\0';
    }

    char current = source_[position_++];

    if (current == '\n') {
        ++line_;
        column_ = 1;
    } else {
        ++column_;
    }

    return current;
}

void Lexer::skipWhitespace() {
    while (!isAtEnd() &&
           std::isspace(static_cast<unsigned char>(peek()))) {
        advance();
    }
}

bool Lexer::isIdentifierStart(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

bool Lexer::isIdentifierContinue(char c) {
    return isIdentifierStart(c) ||
           (c >= '0' && c <= '9');
}

Token Lexer::identifierOrKeyword(
    std::size_t start,
    std::size_t startLine,
    std::size_t startColumn
) {
    while (!isAtEnd() && isIdentifierContinue(peek())) {
        advance();
    }

    std::string_view text(
        source_.data() + start,
        position_ - start
    );

    TokenKind kind = TokenKind::Identifier;

    if (text == "int") {
        kind = TokenKind::KwInt;
    } else if (text == "return") {
        kind = TokenKind::KwReturn;
    } else if (text == "if") {
        kind = TokenKind::KwIf;
    } else if (text == "else") {
        kind = TokenKind::KwElse;
    } else if (text == "while") {
        kind = TokenKind::KwWhile;
    }

    return {
        kind,
        std::string(text),
        startLine,
        startColumn
    };
}

Token Lexer::nextToken() {
    skipWhitespace();

    const std::size_t start = position_;
    const std::size_t startLine = line_;
    const std::size_t startColumn = column_;

    if (isAtEnd()) {
        return {
            TokenKind::EndOfFile,
            "",
            startLine,
            startColumn
        };
    }

    const char c = advance();

    if (isIdentifierStart(c)) {
        return identifierOrKeyword(
            start, startLine, startColumn
        );
    }

    if (c >= '0' && c <= '9') {
        while (!isAtEnd() &&
               peek() >= '0' && peek() <= '9') {
            advance();
        }

        return {
            TokenKind::IntegerLiteral,
            source_.substr(start, position_ - start),
            startLine,
            startColumn
        };
    }

    switch (c) {
        case '+':
            return {TokenKind::Plus, "+", startLine, startColumn};
        case '-':
            return {TokenKind::Minus, "-", startLine, startColumn};
        case '*':
            return {TokenKind::Star, "*", startLine, startColumn};
        case '/':
            return {TokenKind::Slash, "/", startLine, startColumn};

        case '=':
            if (peek() == '=') {
                advance();
                return {
                    TokenKind::EqualEqual, "==",
                    startLine, startColumn
                };
            }
            return {TokenKind::Assign, "=", startLine, startColumn};

        case '!':
            if (peek() == '=') {
                advance();
                return {
                    TokenKind::BangEqual, "!=",
                    startLine, startColumn
                };
            }
            break;

        case '<':
            if (peek() == '=') {
                advance();
                return {
                    TokenKind::LessEqual, "<=",
                    startLine, startColumn
                };
            }
            return {TokenKind::Less, "<", startLine, startColumn};

        case '>':
            if (peek() == '=') {
                advance();
                return {
                    TokenKind::GreaterEqual, ">=",
                    startLine, startColumn
                };
            }
            return {TokenKind::Greater, ">", startLine, startColumn};

        case '(':
            return {
                TokenKind::LeftParen, "(", startLine, startColumn
            };
        case ')':
            return {
                TokenKind::RightParen, ")", startLine, startColumn
            };
        case '{':
            return {
                TokenKind::LeftBrace, "{", startLine, startColumn
            };
        case '}':
            return {
                TokenKind::RightBrace, "}", startLine, startColumn
            };
        case ';':
            return {
                TokenKind::Semicolon, ";", startLine, startColumn
            };
        case ',':
            return {
                TokenKind::Comma, ",", startLine, startColumn
            };
        default:
            break;
    }

    return {
        TokenKind::Unknown,
        std::string(1, c),
        startLine,
        startColumn
    };
}

} // namespace lexer