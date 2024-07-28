#pragma once

#include "build.h"
#include "error.h"
#include "lexer.h"
#include "parser.h"
#include "sob.h"

namespace sob {
    class Test {
    public:
        std::string sob_setPathToSobFile(const char *path);

        Lexer::Token::TokenID lexer_Token_defineID(const std::string &word);
        Lexer::vec_tokens_rows lexer_splitByTokens(const std::vector<std::string> &build_file_rows);

        std::vector<Lexer::Token> parser_toPolishNotaion(const Lexer::pair_vec_tokens_string &row, std::size_t &row_number);
        bool parser_parsCondition(const Lexer::pair_vec_tokens_string &row, std::size_t &row_number);
        sob::Build::var_t parser_parsConditionalConstruction(const sob::Build::var_t &vars, const Lexer::vec_tokens_rows &rows, std::size_t &row_number);
        sob::Build::var_t parser_parsRow(const sob::Build::var_t &vars, const Lexer::vec_tokens_rows &rows, std::size_t &row_number);
    };
} // namespace sob

bool operator==(const sob::Lexer::Token &a, const sob::Lexer::Token &b);
