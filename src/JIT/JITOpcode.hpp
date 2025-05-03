//
// Created by z1w2 on 03.05.2025.
//

#ifndef JITOPCODE_HPP
#define JITOPCODE_HPP

namespace flopy::jit {
    enum JITOpcode {
        LOAD_FUNCTION,          // push function to call stack
        LOAD_CONST,             // LOAD_CONST push r-value to stack
        CALL,                   // call top function from stack
        POP_TOP,                // remove top stack
        STORE_VAR,              // create and set variable (set by top of stack)
        LOAD_VAR,               // push value of variable to stack
        /*
         * NOTE:
         * in main scope return opcode equals exit(value)
         */
        RETURN_CONST,           // return r-value
        RETURN_VALUE,           // return top value from stack
        SYSTEM_CALL,            // do system (built-in) function call
        HALT,                   // similar end of file
    };
}

#endif //JITOPCODE_HPP
