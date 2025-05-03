#include "src/Lexer.hpp"
#include "src/Parser.hpp"
#include "src/JIT/Executor.hpp"

int main(int argc, char *argv[]) {
    flopy::load_plugins();

    std::string test = "puts(\"hello world\")";
    auto lexs = flopy::tokenize(test);

    flopy::Parser p(lexs);

    auto x = p.parsing();

    flopy::jit::Executor program(x);
    program.exec();
}
