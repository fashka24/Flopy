//
// Created by z1w2 on 03.05.2025.
//

#ifndef PARSER_HPP
#define PARSER_HPP

#include <stdexcept>
#include <vector>

#include "Expr.hpp"
#include "Exprs.hpp"
#include "Lexer.hpp"
#include "Statement.hpp"
#include "JIT/JITInstuction.hpp"

namespace flopy {
    class Parser {
    private:
        std::vector<Token> toks;
        size_t size_, pos_;
        std::vector<jit::JITInstruction> instructions_;

        Token current() {
            if (pos_ >= size_) {
                throw std::runtime_error("No more tokens available");
            }
            return toks[pos_];
        }

        Token eat(TT t) {
            if (current().type != t) {
                throw std::runtime_error("Expected token");
            }
            return toks[pos_++];
        }

        void _parse() {
            auto temp = _expr()->eval(instructions_);
        }

        Expr* _expr() {
            if (current().type == TT::IDENTIFIER) {
                Token name = eat(TT::IDENTIFIER);

                if (current().type == TT::LPAREN) {
                    std::vector<Expr*> expr_args;
                    eat(TT::LPAREN);

                    while (current().type != TT::RPAREN) {
                        expr_args.push_back(_expr());
                        if (current().type != TT::RPAREN) {
                            eat(TT::COMMA);
                        }
                    }
                    eat(TT::RPAREN);

                    std::vector<XValue> args;
                    for (auto& expr_arg : expr_args) {
                        args.push_back(expr_arg->eval(instructions_));
                    }

                    return new FunctionExecExpr(name.value, args);
                }
            }
            else if (current().type == TT::STRING_LIT) {
                Token temp = eat(TT::STRING_LIT);
                return new StringExpr(temp.value);
            }
            throw std::runtime_error("Unexpected token type in expression");
        }

    public:
        explicit Parser(const std::vector<Token>& toks)
            : toks(toks), size_(toks.size()), pos_(0) {}

        std::vector<jit::JITInstruction> parsing() {
            while (pos_ < size_ && current().type != TT::END_OF_FILE) {
                _parse();
                pos_++;
            }
            instructions_.push_back({
                jit::HALT, FL_NULL
            });

            return instructions_;
        }
    };
}

#endif // PARSER_HPP
