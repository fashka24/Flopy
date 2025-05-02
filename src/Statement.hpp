//
// Created by z1w2 on 02.05.2025.
//

#ifndef STATEMENT_HPP
#define STATEMENT_HPP
#include <string>
#include <vector>

#include "XValue.hpp"

namespace flopy {
    class Statement {
    public:
        virtual void execute() {}
    };
}

#endif //STATEMENT_HPP
