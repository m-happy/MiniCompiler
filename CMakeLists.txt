
cmake_minimum_required(VERSION 3.20)

project(MiniCompiler
    VERSION 0.1.0
    DESCRIPTION "A small compiler frontend built from scratch"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(lexer
    src/Token.cpp
    src/Lexer.cpp
)

target_include_directories(lexer
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(minic
    src/main.cpp
)

target_link_libraries(minic PRIVATE lexer)

include(CTest)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()