//
// Created by z1w2 on 02.05.2025.
//

#ifndef XVALUE_HPP
#define XVALUE_HPP
#include <string>
#include <variant>
#include <vector>

namespace flopy {
    std::string multiply_string(const std::string& str, int times) {
        if (times < 0) {
            throw std::runtime_error("Number of times must be non-negative");
        }

        std::string result;
        for (int i = 0; i < times; ++i) {
            result += str;
        }
        return result;
    }
    enum XValueType {
        VOID,
        INT, FLOAT, STRING, LIST,
    };
    class XValue {
private:
    std::variant<std::monostate, int, float, std::string, std::vector<XValue>> value_;
    XValueType type;

public:
    explicit XValue(int value, XValueType t) : value_(value), type(XValueType::INT) {}
    explicit XValue(float value, XValueType t = XValueType::FLOAT) : value_(value), type(XValueType::FLOAT) {}
    explicit XValue(std::string value, XValueType t = XValueType::STRING) : value_(value), type(XValueType::STRING) {}
    explicit XValue(std::vector<XValue> value, XValueType t = XValueType::LIST) : value_(value), type(XValueType::LIST) {}
    explicit XValue() : value_(std::monostate()), type(XValueType::VOID) {}

    template <typename T_>
    T_ get() const { return std::get<T_>(value_); }

    [[nodiscard]] XValueType get_type() const {
        return type;
    }

    bool operator==(const XValue& other) const {
        if (type != other.type) return false;
        return value_ == other.value_;
    }

    bool operator!=(const XValue& other) const {
        return !(*this == other);
    }

    XValue operator+(const XValue& other) const {
        if (type == XValueType::INT && other.type == XValueType::INT) {
            return XValue(get<int>() + other.get<int>(), XValueType::INT);
        }
        if (type == XValueType::FLOAT && other.type == XValueType::FLOAT) {
            return XValue(get<float>() + other.get<float>());
        }
        if (type == XValueType::STRING && other.type == XValueType::STRING) {
            return XValue(get<std::string>() + other.get<std::string>());
        }
        throw std::runtime_error("Unsupported types for addition");
    }

    XValue operator-(const XValue& other) const {
        if (type == XValueType::INT && other.type == XValueType::INT) {
            return XValue(get<int>() - other.get<int>(), XValueType::INT);
        }
        if (type == XValueType::FLOAT && other.type == XValueType::FLOAT) {
            return XValue(get<float>() - other.get<float>());
        }
        throw std::runtime_error("Unsupported types for subtraction");
    }

    XValue operator*(const XValue& other) const {
        if (type == XValueType::INT && other.type == XValueType::INT) {
            return XValue(get<int>() * other.get<int>(), XValueType::INT);
        }
        if (type == XValueType::FLOAT && other.type == XValueType::FLOAT) {
            return XValue(get<float>() * other.get<float>());
        }
        if (type == XValueType::STRING && (other.type == XValueType::INT)) {
            return XValue(multiply_string(get<std::string>(), other.get<int>()), XValueType::STRING);
        }
        if (type == XValueType::STRING && (other.type == XValueType::FLOAT)) {
            return XValue(multiply_string(get<std::string>(), other.get<float>()), XValueType::STRING);
        }
        throw std::runtime_error("Unsupported types for multiplication");
    }

    XValue operator/(const XValue& other) const {
        if (type == XValueType::INT && other.type == XValueType::INT) {
            if (other.get<int>() == 0) throw std::invalid_argument("Division by zero");
            return XValue(get<int>() / other.get<int>(), XValueType::INT);
        }
        if (type == XValueType::FLOAT && other.type == XValueType::FLOAT) {
            if (other.get<float>() == 0.0f) throw std::invalid_argument("Division by zero");
            return XValue(get<float>() / other.get<float>());
        }
        throw std::runtime_error("Unsupported types for division");
    }
};

}

#endif //XVALUE_HPP
