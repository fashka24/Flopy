//
// Created by z1w2 on 03.05.2025.
//

#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP
#include <stack>
#include <vector>

#include "JITInstruction.hpp"
#include "../Globals.hpp"

namespace flopy::jit {
    inline std::vector<XValue> get_n_elements(std::stack<XValue>& s, int n) {
        std::vector<XValue> elements;
        std::stack<XValue> tempStack;

        for (int i = 0; i < n && !s.empty(); ++i) {
            elements.push_back(s.top());
            tempStack.push(s.top());
            s.pop();
        }

        while (!tempStack.empty()) {
            s.push(tempStack.top());
            tempStack.pop();
        }

        return elements;
    }

    class Executor {
    private:
        std::vector<JITInstruction> instructions_;
        std::stack<XValue> stack_;
        std::stack<GlobalFunction> call_stack_;
        size_t pos;                     // position on instructions table

        JITInstruction fetch_byte() {
            return instructions_[pos];
        }

    public:
        explicit Executor(const std::vector<JITInstruction> &instructions)
            : instructions_(instructions) {
        }

        void exec(size_t _pos = 0) {
            pos = _pos;

            while (fetch_byte().opcode != HALT) {
                _exec();
                pos++;
            }
        }

    private:
        void _syscall(int num) {
            switch (num) {
                case 1: {
                    int exit_code = stack_.top().get<int>();

                    exit(exit_code);
                }
                default:
                    throw std::runtime_error("unknown syscall");
                break;
            }
        }
        void _exec() {
            switch (fetch_byte().opcode) {
                case LOAD_FUNCTION: {
                    call_stack_.push(
                        get_global_func(fetch_byte()
                            .argument
                            .get<std::string>()
                            ));
                    break;
                }
                case LOAD_CONST: {
                    stack_.push(
                        fetch_byte().argument);
                    break;
                }
                case CALL: {
                    short args_number = static_cast<short>(fetch_byte()
                        .argument
                        .get<int>());

                    auto _tmp = call_stack_.top();
                    auto _tmp_s = get_n_elements(stack_, args_number);

                    auto _tmp_result = _tmp(_tmp_s);
                    if (_tmp_result.get_type() != XValueType::VOID)
                        stack_.push(_tmp_result);
                    break;
                }
                case POP_TOP: {
                    stack_.pop();
                    break;
                }
                case STORE_VAR: {
                    auto name = fetch_byte().argument.get<std::string>();

                    variables[name].value = stack_.top(); stack_.pop();
                    break;
                }
                case LOAD_VAR: {
                    auto name = fetch_byte().argument.get<std::string>();

                    stack_.push(get_global_variable(name).value);
                    break;
                }
                case SYSTEM_CALL: {
                    int num_of_syscall = fetch_byte().argument.get<int>();

                    _syscall(num_of_syscall);
                    break;
                }
                default:
                    throw std::runtime_error("Unknown instruction");
                    break;
            }
        }
    };
}

#endif //EXECUTOR_HPP
