//
// Created by z1w2 on 02.05.2025.
//

#ifndef STD_HPP
#define STD_HPP

#include "IPlugin.hpp"
#include "../Globals.hpp"
#include <iostream>

namespace flopy {
    class STDPlugin: public IPlugin {
    public:
        std::map<std::string, std::function<XValue(std::vector<XValue>&)>> createFunctions() override {
            return {
            {"puts", [](std::vector<XValue>& args) {
                for (auto arg : args) {\

                    if (arg.get_type() == XValueType::STRING)
                        std::cout << arg.get<std::string>() << "\n";
                }

                return XValue(0);
            }},
        };
        }
    };
}

#endif //STD_HPP
