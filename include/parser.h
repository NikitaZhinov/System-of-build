#pragma once

#include "common.h"

#include <fstream>
#include <vector>

class Parser {
private:
    static const std::vector<char> OPERATORS;

    static bool findOperator(char op);

public:
    static Error parsFile(std::ifstream &file);
};
