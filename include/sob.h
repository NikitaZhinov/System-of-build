#pragma once

#include "common.h"
#include "parser.h"

namespace sob {
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

    Error Sob::error_code = OK;
    std::string Sob::path_to_buildfile = ".sob";
    std::ifstream Sob::file;
    std::vector<std::string> Sob::code;
} // namespace sob
