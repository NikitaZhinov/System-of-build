#include "../include/parser.h"

const std::vector<char> Parser::OPERATORS = {
    '=', '(', ')', ','
};

bool Parser::findOperator(char op) {
    for (char elem : OPERATORS)
        if (elem == op)
            return true;
    return false;
}

Error Parser::parsFile(std::ifstream &file) {
    Error error_code = OK;

    std::string command;
    char current_symbol = 0;
    while (file.get(current_symbol)) {
        if (current_symbol == ' ' || current_symbol == '\t' || current_symbol == '\n') {

        } else if (findOperator(current_symbol)) {

        } else {
        }
    }

    return error_code;
}
