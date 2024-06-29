#pragma once

#include <fstream>
#include <print>
#include <string>
#include <vector>

enum Error {
    OK,
    File_not_found,
    Invalid_input_parametrs,
};

struct Variable {
    std::string name;
};
