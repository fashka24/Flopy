//
// Created by z1w2 on 02.05.2025.
//

#ifndef EXPR_HPP
#define EXPR_HPP
#include "XValue.hpp"
#include "JIT/JITInstruction.hpp"

namespace flopy {
    class Expr {
    public:
        virtual XValue eval(std::vector<jit::JITInstruction>& instructions) {
            return XValue();
        }
    };
    class VoidExpr: public Expr{
    public:
        VoidExpr() {}

        XValue eval(std::vector<jit::JITInstruction>& instructions) override {
            return XValue();
        }
    };
}

#endif //EXPR_HPP
