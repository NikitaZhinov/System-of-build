#include "parser.h"

namespace sob {
    Error Parser::parsFile(std::ifstream &file) {
        Error error_code = OK;

        std::string command;
        char current_symbol = 0;
        while (file.get(current_symbol)) {
            if (current_symbol == ' ' || current_symbol == '\t' || current_symbol == '\n') {

            } else {
            }
        }

        return error_code;
    }
}
