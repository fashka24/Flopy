//
// Created by z1w2 on 02.05.2025.
//

#ifndef STD_HPP
#define STD_HPP

#include "IPlugin.hpp"
#include <iostream>
#include <sstream>

namespace flopy {
    class STDPlugin: public IPlugin {
    private:
        std::string xvalue2str(XValue arg) {
            std::stringstream ss;

            if (arg.get_type() == XValueType::STRING)
                ss << arg.get<std::string>();
            if (arg.get_type() == XValueType::INT)
                ss << arg.get<int>();
            if (arg.get_type() == XValueType::FLOAT)
                ss << arg.get<float>();
            if (arg.get_type() == XValueType::LIST) {
                ss << "[";
                auto _sv = arg.get<std::vector<XValue>>();
                auto _sz = _sv.size();
                for (int i = 0; i < _sz; ++i) {
                    ss << xvalue2str(_sv[i]);
                    if (i + 1 != _sz)
                        ss << ", ";
                }
                ss << "]";
            }

            return ss.str();
        }
    public:
        std::map<std::string, std::function<XValue(std::vector<XValue>&)>> createFunctions() override {
            return {
            {"puts", [this](std::vector<XValue>& args) {
                for (auto arg : args) {
                    std::cout << this->xvalue2str(arg);
                }

                return XValue(0);
            }},
    {"echo", [this](std::vector<XValue>& args) {
            for (auto arg : args) {
                std::cout << this->xvalue2str(arg) << "\n";
            }

            return XValue(0);
        }},
                {"str", [this](std::vector<XValue>& args) {
                    XValue temp{0};

                    if (args.size() <= 0 && args.size() >= 2)
                        throw std::runtime_error("too few arguments for function \"str\"");

                    temp = XValue(this->xvalue2str(args[0]), XValueType::STRING);

                    return temp;
                }},
                {"add", [](std::vector<XValue>& args) {
                    XValue v{};
                    if (args.size() <= 0 && args.size() >= 3)
                        throw std::runtime_error("too few arguments for function \"add\"");
                    v = args[0] + args[1];
                    return v;
                }},
                {"sub", [](std::vector<XValue>& args) {
                    XValue v{};
                    if (args.size() <= 0 && args.size() >= 3)
                        throw std::runtime_error("too few arguments for function \"sub\"");
                    v = args[0] - args[1];
                    return v;
                }},
                {"mul", [](std::vector<XValue>& args) {
                    XValue v{};
                    if (args.size() <= 0 && args.size() >= 3)
                        throw std::runtime_error("too few arguments for function \"mul\"");
                    v = args[0] * args[1];
                    return v;
                }},
                {"div", [](std::vector<XValue>& args) {
                    XValue v{};
                    if (args.size() <= 0 && args.size() >= 3)
                        throw std::runtime_error("too few arguments for function \"div\"");
                    v = args[0] / args[1];
                    return v;
                }},
        };
        }

        std::map<std::string, XValue> createVariables() override {
            return {
                {"endl", XValue("\n", XValueType::STRING)},
                {"false", XValue(0, XValueType::INT)},
                {"true", XValue(1, XValueType::INT)},
            };
        }
    };
}

#endif //STD_HPP
