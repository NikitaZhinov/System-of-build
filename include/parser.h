#pragma once

#include "common.h"

class Parser {
public:
    static Error parsFile(std::ifstream &file);
};
