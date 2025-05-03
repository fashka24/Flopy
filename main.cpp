#include <iostream>
#include <fstream>
#include <sstream>

#include "src/Lexer.hpp"
#include "src/Parser.hpp"
#include "src/JIT/Executor.hpp"

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        std::cout <<
            "Flopy interpreter\n"
        <<  "Usage: fli <file>.flp\n";
        return 0;
    }
    else if (argc >= 2) {
        flopy::load_plugins();

        std::string path = argv[1];

        std::string text;
        {
            std::ifstream f(path);
            std::stringstream buffer;
            if (f.is_open()) {
                buffer << f.rdbuf();
                f.close();
            }
            else {
                throw std::runtime_error("not found file " + path);
                return 1;
            }
            text = buffer.str();
        }

        auto lex = flopy::tokenize(text);

        flopy::Parser p(lex);

        auto x = p.parsing();

        flopy::jit::Executor program(x);
        program.exec();
    }
    // flopy::load_plugins();
    //
    // std::string test = "puts(\"hello world\")";
    // auto lexs = flopy::tokenize(test);
    //
    // flopy::Parser p(lexs);
    //
    // auto x = p.parsing();
    //
    // flopy::jit::Executor program(x);
    // program.exec();
}
