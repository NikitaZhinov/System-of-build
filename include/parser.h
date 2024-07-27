#pragma once

#include "build.h"
#include "error.h"
#include "lexer.h"

namespace sob {
    class Test;

    /**
     * @brief A class for parsing Lexer tokens.
     */
    class Parser {
        friend Test;

        /**
         * @brief A copy of the tokens of the Lexer.
         */
        const Lexer::vec_tokens_rows tokens;

        /**
         * @brief A pointer to the build class that is being filled in.
         */
        Build *build_class;

        /**
         * @brief A pointer to the error_code from SOB class.
         */
        Error *error_code;

        /**
         * @brief Sets error id as Syntax and text as "Syntax error! {Error description} on the {Line number} line: {Line text}".
         *
         * @param row - line text.
         * @param row_number - line number.
         * @param text - error description.
         */
        void setError(const std::string &row, std::size_t row_number, const std::string &text);

        /**
         * @brief Rewrites the string with the condition into Polish notation.
         *
         * @param row - the string with the condition.
         * @param row_number - line number.
         *
         * @return A string in Polish notation.
         */
        std::vector<Lexer::Token> toPolishNotaion(const Lexer::vec_tokens &row, std::size_t &row_number);

        /**
         * @brief Parses the string with the condition.
         *
         * @param row - the string with the condition.
         * @param row_number - line number.
         *
         * @return True or false.
         */
        bool parsCondition(const Lexer::vec_tokens &row, std::size_t &row_number);

        /**
         * @brief Parses the conditional consturtion.
         *
         * @param row - a const iterator to the current line with a conditional.
         * @param row_number - line number.
         */
        void parsConditionalConstruction(Lexer::vec_tokens_rows::const_iterator &row, std::size_t &row_number);

        /**
         * @brief Parses the current line.
         *
         * @param row - a const iterator to the current line.
         * @param row_number - line number.
         *
         * @return If an error has occurred, then the truth is otherwise false.
         */
        bool parsRow(Lexer::vec_tokens_rows::const_iterator &row, std::size_t &row_number);

    public:
        /**
         * @brief A constructor.
         *
         * @param tokens - a tokens from Lexer.
         * @param build_class - a pointer to build class that is being filled in.
         * @param error_code - a pointer to the error_code from SOB class.
         */
        Parser(const Lexer::vec_tokens_rows &tokens, Build *build_class, Error *error_code);

        /**
         * @brief Parses a tokens of the Lexer.
         */
        void parsTokens();
    };
} // namespace sob
