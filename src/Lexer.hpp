//
// Created by z1w2 on 02.05.2025.
//

#ifndef LEXER_HPP
#define LEXER_HPP
#include <string>
#include <vector>

namespace flopy {
    enum TT {
        IDENTIFIER,
        LPAREN, RPAREN,
        COMMA, EQ,
        STRING_LIT,
        NUM_LIT, DOT,

        END_OF_FILE,
    };
    struct Token {
        TT type;
        std::string value;
    };

    std::vector<Token> tokenize(std::string source) {
        std::vector<Token> rs;
        std::string buffer;
        size_t size = source.size();

        for (int i = 0; i < size; ++i) {
            if (isspace(source[i])) continue;

            if (source[i] == '#') while (i < size && source[i] != '\n') i++;

            if (source[i] == '(') rs.push_back({TT::LPAREN, "("});
            else if (source[i] == ')') rs.push_back({TT::RPAREN, ")"});
            else if (source[i] == ',') rs.push_back({TT::COMMA, ","});
            else if (source[i] == '.') rs.push_back({TT::DOT, "."});
            else if (source[i] == '=') rs.push_back({TT::EQ, "="});

            else if (isalpha(source[i]) || source[i] == '_') {
                while (isalnum(source[i]) || source[i] == '_') {
                    buffer += source[i];
                    i++;
                }
                i--;

                rs.push_back({TT::IDENTIFIER, buffer});
            }
            else if (source[i] == '"') {
                i++;
                while (source[i] != '"') {
                    if (source[i] == '\\') {
                        i++;
                        if (source[i] == '"') buffer += "\"";
                        if (source[i] == 'n') buffer += "\n";
                        if (source[i] == 'r') buffer += "\r";
                        if (source[i] == 't') buffer += "\t";
                        if (source[i] == '\\') buffer += "\\";
                    }
                    else
                        buffer += source[i];
                    i++;
                }

                rs.push_back({TT::STRING_LIT, buffer});
            }
            else if (isdigit(source[i])) {
                while (isdigit(source[i])) {
                    buffer += source[i];
                    i++;
                }
                i--;

                rs.push_back({TT::NUM_LIT, buffer});
            }

            buffer.clear();
        }
        rs.push_back({TT::END_OF_FILE, "eof"});

        return rs;
    }
}

#endif //LEXER_HPP
