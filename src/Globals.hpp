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
#include "Expr.hpp"
#include "Exprs.hpp"
#include "plugins/Plugins.hpp"

namespace flopy {
    inline XValue FL_NULL = XValue(1);
    using GlobalFunction = std::function<XValue(std::vector<XValue>&)>;

    struct GlobalVariable {
        XValue value;
    };
    /**
     *
     */
    inline
    std::map<std::string, GlobalFunction>
        functions;
    inline
    std::map<std::string, GlobalVariable>
        variables;

    inline void load_plugins() {
        for (auto plugin: plugins) {
            auto _tmp = plugin->createFunctions();
            for (auto& tmp: _tmp) {
                functions[tmp.first] = tmp.second;
            }
        }
    }
    inline GlobalFunction get_global_func(const std::string& name) {
        for (auto& func: functions) {
            if (func.first == name)
                return func.second;
        }
        throw std::runtime_error("unknown function " + name);
    }
    inline bool is_global_func(const std::string& name) {
        for (auto& func: functions) {
            if (func.first == name)
                return true;
        }
        return false;
    }
    inline GlobalVariable get_global_variable(const std::string& name) {
        for (auto& var: variables) {
            if (var.first == name)
                return var.second;
        }
        throw std::runtime_error("unknown variable " + name);
    }
}

#endif //GLOBALS_HPP
