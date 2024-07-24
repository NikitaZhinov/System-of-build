#pragma once

#include "build.h"
#include "error.h"
#include "lexer.h"

namespace sob {
    class Parser {
        const Lexer::vec_tokens_rows tokens;
        Build *build_class;
        Error *error_code;

        void setError(const std::string &row, std::size_t row_number, const std::string &text);
        std::vector<Lexer::Token> toPolishNotaion(const Lexer::vec_tokens &row, std::size_t &row_number);
        bool parsCondition(const Lexer::vec_tokens &row, std::size_t &row_number);
        void conditionalConstructionPars(Lexer::vec_tokens_rows::const_iterator &row, std::size_t &row_number);
        bool parsRow(Lexer::vec_tokens_rows::const_iterator &row, std::size_t &row_number);

    public:
        Parser(const Lexer::vec_tokens_rows &tokens, Build *build_class, Error *error_code);

        void parsTokens();
    };
} // namespace sob
