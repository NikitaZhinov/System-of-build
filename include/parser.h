#pragma once

#include "common.h"

namespace sob {
    class Parser {
    public:
        static Error parsFile(std::ifstream &file);
    };
} // namespace sob
