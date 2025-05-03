cmake_minimum_required(VERSION 3.30)
project(Flopy)

set(CMAKE_CXX_STANDARD 20)

add_executable(Flopy main.cpp
        src/Lexer.hpp
        src/XValue.hpp
        src/Expr.hpp
        src/Expr.hpp
        src/Statement.hpp
        src/Globals.hpp
        src/Exprs.hpp
        src/plugins/IPlugin.hpp
        src/plugins/STD.hpp
        src/plugins/Plugins.hpp
        src/JIT/JITOpcode.hpp
        src/JIT/JITInstuction.hpp
        src/JIT/Executor.hpp
        src/Parser.hpp)
