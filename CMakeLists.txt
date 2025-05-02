cmake_minimum_required(VERSION 3.30)
project(Flopy)

set(CMAKE_CXX_STANDARD 20)

add_executable(Flopy main.cpp
        src/Lexer.hpp
        src/XValue.hpp
        src/Expr.hpp)
