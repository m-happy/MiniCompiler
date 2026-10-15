
#pragma once

#include <cstddef>
#include <string>
#include <string_view>

namespace lexer {

enum class TokenKind {
    // Special tokens
    Unknown,
    EndOfFile,

    // Names and literals
    Identifier,
    IntegerLiteral,

    // Keywords
    KwInt,
    KwReturn,
    KwIf,
    KwElse,
    KwWhile,

    // Arithmetic operators
    Plus,
    Minus,
    Star,
    Slash,

    // Assignment and comparison operators
    Assign,
    EqualEqual,
    BangEqual,
    Less,
    LessEqual,
    Greater,
    GreaterEqual,

    // Punctuation
    LeftParen,
    RightParen,
    LeftBrace,
    RightBrace,
    Semicolon,
    Comma
};

struct Token {
    TokenKind kind;
    std::string lexeme;
    std::size_t line;
    std::size_t column;
};

std::string_view tokenKindName(TokenKind kind);

} // namespace lexer