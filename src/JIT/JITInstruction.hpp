//
// Created by z1w2 on 03.05.2025.
//

#ifndef JITINSTUCTION_HPP
#define JITINSTUCTION_HPP
#include "JITOpcode.hpp"
#include "../XValue.hpp"

/*
 * NOTE:
 * byte code has 1 argument syntax
 * :)
 */

namespace flopy::jit {
    using JITOperand = XValue;

    struct JITInstruction {
        JITOpcode opcode{};
        JITOperand argument;
    };
}

#endif //JITINSTUCTION_HPP
