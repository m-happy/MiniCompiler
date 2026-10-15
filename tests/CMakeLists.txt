
add_executable(lexer_tests
    LexerTests.cpp
)

target_link_libraries(lexer_tests PRIVATE lexer)

add_test(NAME LexerTests COMMAND lexer_tests)