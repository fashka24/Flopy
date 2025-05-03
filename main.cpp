#include "src/Lexer.hpp"

int main(int argc, char *argv[]) {
    std::string test = "puts(\"hello world\n\")";
    auto lexs = flopy::tokenize(test);
}
