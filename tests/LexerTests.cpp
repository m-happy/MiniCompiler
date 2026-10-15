
#include "lexer/Lexer.h"
#include "lexer/Token.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstddef>

namespace {

int testsPassed = 0;
int testsFailed = 0;

void expect(
    bool condition,
    const std::string& testName
) {
    if (condition) {
        ++testsPassed;
        std::cout << "[PASS] " << testName << '\n';
    } else {
        ++testsFailed;
        std::cerr << "[FAIL] " << testName << '\n';
    }
}

void testKeyword() {
    lexer::Lexer lexer("int");

    const lexer::Token token = lexer.nextToken();

    expect(
        token.kind == lexer::TokenKind::KwInt,
        "recognizes the int keyword"
    );

    expect(
        token.lexeme == "int",
        "preserves the keyword text"
    );
}

void testIdentifier() {
    lexer::Lexer lexer("answer");

    const lexer::Token token = lexer.nextToken();

    expect(
        token.kind == lexer::TokenKind::Identifier,
        "recognizes an identifier"
    );

    expect(
        token.lexeme == "answer",
        "preserves the identifier text"
    );
}

void testIntegerLiteral() {
    lexer::Lexer lexer("42");

    const lexer::Token token = lexer.nextToken();

    expect(
        token.kind == lexer::TokenKind::IntegerLiteral,
        "recognizes an integer literal"
    );

    expect(
        token.lexeme == "42",
        "preserves the integer text"
    );
}

void testTwoCharacterOperator() {
    lexer::Lexer lexer("==");

    const lexer::Token token = lexer.nextToken();

    expect(
        token.kind == lexer::TokenKind::EqualEqual,
        "recognizes the == operator"
    );

    expect(
        token.lexeme == "==",
        "preserves the operator text"
    );
}

void testSourcePosition() {
    lexer::Lexer lexer("int\nanswer");

    const lexer::Token first = lexer.nextToken();
    const lexer::Token second = lexer.nextToken();

    expect(
        first.line == 1 && first.column == 1,
        "records the first token's position"
    );

    expect(
        second.line == 2 && second.column == 1,
        "updates position after a newline"
    );
}

void testEndOfFile() {
    lexer::Lexer lexer("42");

    lexer.nextToken();

    const lexer::Token token = lexer.nextToken();

    expect(
        token.kind == lexer::TokenKind::EndOfFile,
        "returns EOF after the last token"
    );
}

void expectTokenKind(
    lexer::Lexer& lexer,
    lexer::TokenKind expectedKind,
    const std::string& testName
) {
    const lexer::Token token = lexer.nextToken();

    if (token.kind == expectedKind) {
        ++testsPassed;
        std::cout << "[PASS] " << testName << '\n';
    } else {
        ++testsFailed;
        std::cerr
            << "[FAIL] " << testName
            << "\n  Expected: "
            << lexer::tokenKindName(expectedKind)
            << "\n  Actual:   "
            << lexer::tokenKindName(token.kind)
            << "\n  Lexeme:   \"" << token.lexeme << "\""
            << "\n  Position: " << token.line
            << ":" << token.column << '\n';
    }
}

void testMiniProgram() {
    lexer::Lexer lexer("int answer = 42 + 10;");

    const lexer::TokenKind expected[] = {
        lexer::TokenKind::KwInt,
        lexer::TokenKind::Identifier,
        lexer::TokenKind::Assign,
        lexer::TokenKind::IntegerLiteral,
        lexer::TokenKind::Plus,
        lexer::TokenKind::IntegerLiteral,
        lexer::TokenKind::Semicolon,
        lexer::TokenKind::EndOfFile
    };

    for (std::size_t i = 0;
         i < sizeof(expected) / sizeof(expected[0]);
         ++i) {
        expectTokenKind(
            lexer,
            expected[i],
            "mini-program token #" + std::to_string(i + 1)
        );
    }
}


} // namespace

int main() {
    testKeyword();
    testIdentifier();
    testIntegerLiteral();
    testTwoCharacterOperator();
    testSourcePosition();
    testEndOfFile();
    testMiniProgram();
    std::cout << "\nTests passed: " << testsPassed
              << "\nTests failed: " << testsFailed << '\n';

    return testsFailed == 0
        ? EXIT_SUCCESS
        : EXIT_FAILURE;
}