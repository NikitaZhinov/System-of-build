#pragma once

#include <fstream>
#include <print>
#include <string>
#include <vector>

namespace sob {
    enum Error {
        OK,
        File_not_found,
        Invalid_input_parametrs,
    };

    struct Variable {
        std::string name;
    };
} // namespace sob
