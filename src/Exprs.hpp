//
// Created by z1w2 on 02.05.2025.
//

#ifndef EXPRS_HPP
#define EXPRS_HPP
#include "Expr.hpp"
#include "Globals.hpp"

namespace flopy {
    class StringExpr: public Expr {
    private:
        XValue value_;
    public:
        virtual ~StringExpr() = default;

        explicit StringExpr(const std::string &value)
            : value_(value, XValueType::STRING) {
        }

        XValue eval(std::vector<jit::JITInstruction>& instructions) override {
            instructions.push_back({
                jit::LOAD_CONST, value_
            });
            return value_;
        }
    };
    class IntExpr: public Expr {
    private:
        XValue value_;
    public:
        explicit IntExpr(const int &value)
            : value_(value, XValueType::INT) {
        }

        XValue eval(std::vector<jit::JITInstruction>& instructions) override {
            instructions.push_back({
                jit::LOAD_CONST, value_
            });
            return value_;
        }
    };
    class FloatExpr: public Expr {
    private:
        XValue value_;
    public:
        explicit FloatExpr(const float &value)
            : value_(value, XValueType::FLOAT) {
        }

        XValue eval(std::vector<jit::JITInstruction>& instructions) override {
            instructions.push_back({
                jit::LOAD_CONST, value_
            });
            return value_;
        }
    };
    class FunctionExecExpr: public Expr {
    private:
        std::string name;
        std::vector<XValue> args;

    public:
        FunctionExecExpr(const std::string &name, const std::vector<XValue> &args)
            : name(name),
              args(args) {
        }

        virtual ~FunctionExecExpr() = default;

        XValue eval(std::vector<jit::JITInstruction> &instructions) override {
            instructions.push_back({
                jit::LOAD_FUNCTION, XValue(name, XValueType::STRING)
            });
            instructions.push_back({
                jit::CALL, XValue(static_cast<int>(args.size()), XValueType::INT)
            });
            return {0};
        }
    };
}

#endif //EXPRS_HPP
