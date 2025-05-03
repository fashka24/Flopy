//
// Created by z1w2 on 02.05.2025.
//

#ifndef IPLUGIN_HPP
#define IPLUGIN_HPP
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "../Expr.hpp"

namespace flopy {
    class IPlugin {
    public:
        virtual std::map<std::string, std::function<XValue(std::vector<XValue>&)>> createFunctions() {
            return {};
        }
    };
}

#endif //IPLUGIN_HPP
