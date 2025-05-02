//
// Created by z1w2 on 02.05.2025.
//

#ifndef EXPR_HPP
#define EXPR_HPP
#include "Globals.hpp"
#include "XValue.hpp"

namespace flopy {
    class Expr {
    public:
        virtual XValue eval() {
            return {0};
        }
    };

    class StringExpr: public Expr {
    private:
        XValue value_;
    public:
        explicit StringExpr(const std::string &value)
            : value_(value, XValueType::STRING) {
        }

        XValue eval() override {
            return value_;
        }
    };
    class FunctionExecutingExpr: public Expr {
    private:
        std::string name;
        std::vector<XValue> args;

    public:
        FunctionExecutingStatement(const std::string &name, const std::vector<XValue> &args)
            : name(name),
              args(args) {
        }

        XValue eval() override {
            return functions[name](args);
        }
    };
}

#endif //EXPR_HPP
