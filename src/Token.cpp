
#include "lexer/Token.h"

namespace lexer {

std::string_view tokenKindName(TokenKind kind) {
    switch (kind) {
        case TokenKind::Unknown:        return "Unknown";
        case TokenKind::EndOfFile:      return "EndOfFile";

        case TokenKind::Identifier:     return "Identifier";
        case TokenKind::IntegerLiteral: return "IntegerLiteral";

        case TokenKind::KwInt:          return "KwInt";
        case TokenKind::KwReturn:       return "KwReturn";
        case TokenKind::KwIf:           return "KwIf";
        case TokenKind::KwElse:         return "KwElse";
        case TokenKind::KwWhile:        return "KwWhile";

        case TokenKind::Plus:           return "Plus";
        case TokenKind::Minus:          return "Minus";
        case TokenKind::Star:           return "Star";
        case TokenKind::Slash:          return "Slash";

        case TokenKind::Assign:         return "Assign";
        case TokenKind::EqualEqual:     return "EqualEqual";
        case TokenKind::BangEqual:      return "BangEqual";
        case TokenKind::Less:           return "Less";
        case TokenKind::LessEqual:      return "LessEqual";
        case TokenKind::Greater:        return "Greater";
        case TokenKind::GreaterEqual:   return "GreaterEqual";

        case TokenKind::LeftParen:      return "LeftParen";
        case TokenKind::RightParen:     return "RightParen";
        case TokenKind::LeftBrace:      return "LeftBrace";
        case TokenKind::RightBrace:     return "RightBrace";
        case TokenKind::Semicolon:      return "Semicolon";
        case TokenKind::Comma:          return "Comma";
    }

    // Defensive fallback for an invalid enum value.
    return "Unknown";
}

} // namespace lexer