//
// Created by z1w2 on 02.05.2025.
//

#ifndef XVALUE_HPP
#define XVALUE_HPP
#include <string>
#include <variant>
#include <vector>

namespace flopy {
    enum XValueType {
        INT, FLOAT, STRING, LIST,
    };
    class XValue {
    private:
        std::variant<int, float, std::string, std::vector<XValue>>
            value_;
        XValueType type;

    public:
        XValue(int value, XValueType type)
            : type(type) {
            value_ = value;
        }
        XValue(float value, XValueType type)
            : type(type) {
            value_ = value;
        }
        XValue(std::string value, XValueType type)
            : type(type) {
            value_ = value;
        }
        XValue(std::vector<XValue> value, XValueType type)
            : type(type) {
            value_ = value;
        }

        template <typename T_>
        T_ get() { return std::get<T_>(value_); }
    };
}

#endif //XVALUE_HPP
