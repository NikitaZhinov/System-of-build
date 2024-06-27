export module SoB;

#include <print>
#include <vector>

import common;
import operators;

export namespace sob {
    std::vector<Operator> OPERATORS = {
        {"=", assignment},
        {"(", assignment},
    };

    int run(int argc, const char **argv) {
        return 0;
    }
} // namespace sob
