#pragma once

#include "common.h"
#include "parser.h"

class Sob {
    static Error error_code;
    static std::string path_to_buildfile;
    static std::ifstream file;
    static std::vector<std::string> code;

public:
    static void parsInputParametrs(int argc, const char **argv);
    static void getFile();
    static void parsFile();

    static Error run(int argc, const char **argv);
};
