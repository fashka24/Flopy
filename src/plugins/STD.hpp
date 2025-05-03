//
// Created by z1w2 on 02.05.2025.
//

#ifndef STD_HPP
#define STD_HPP

#include "IPlugin.hpp"
#include <iostream>

namespace flopy {
    class STDPlugin: public IPlugin {
    public:
        std::map<std::string, std::function<XValue(std::vector<XValue>&)>> createFunctions() override {
            return {
            {"puts", [](std::vector<XValue>& args) {
                for (auto arg : args) {

                    if (arg.get_type() == XValueType::STRING)
                        std::cout << arg.get<std::string>();
                }

                return XValue(0);
            }},
    {"echo", [](std::vector<XValue>& args) {
        for (auto arg : args) {

            if (arg.get_type() == XValueType::STRING)
                std::cout << arg.get<std::string>() << "\n";
            }

            return XValue(0);
        }},
                {"str", [](std::vector<XValue>& args) {
                    XValue temp{0};

                    if (args.size() <= 0 && args.size() >= 2)
                        throw std::runtime_error("too few arguments for function \"str\"");

                    if (args[0].get_type() == XValueType::INT)
                        temp = XValue(std::to_string(args[0].get<int>()), XValueType::STRING);
                    else if (args[0].get_type() == XValueType::FLOAT)
                        temp = XValue(std::to_string(args[0].get<float>()), XValueType::STRING);
                    else
                        temp = args[0];

                    return temp;
                }},
        };
        }
    };
}

#endif //STD_HPP
