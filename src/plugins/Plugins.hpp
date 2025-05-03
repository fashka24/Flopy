//
// Created by z1w2 on 02.05.2025.
//

#ifndef PLUGINS_HPP
#define PLUGINS_HPP
#include <vector>

#include "IPlugin.hpp"
#include "STD.hpp"

namespace flopy {
    inline std::vector<IPlugin*> plugins{
        new STDPlugin(),
    };
}

#endif //PLUGINS_HPP
