//
// Created by z1w2 on 02.05.2025.
//

#ifndef GLOBALS_HPP
#define GLOBALS_HPP
#include <functional>
#include <iostream>
#include <map>
#include <string>

#include "XValue.hpp"

namespace flopy {
    inline XValue FL_NULL = XValue(0);
    inline
    std::map<std::string, std::function<XValue(std::vector<XValue>&)>>
        functions {
            {"puts", [](std::vector<XValue>& args) {
                for (auto arg: args) {
                    if (arg.get_type() == XValueType::STRING)
                        std::cout << arg.get<std::string>() << "\n";
                }

                return FL_NULL;
            }},
        };
}

#endif //GLOBALS_HPP
