#pragma once

#include "build.h"

#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace sob {
    /**
     * @brief Static class.
     * Splits text of build file by tokens.
     */
    class Lexer {
    public:
        /**
         * @brief All keywords from syntax.
         */
        static const std::set<std::string> KEY_WORDS;

        /**
         * @brief A string with all operator characters.
         */
        static const std::string OPERATOR_CHARS;

        /**
         * @brief A string with all paired operator characters.
         */
        static const std::string PAIRED_OPERATOR_CHARS;

        /**
         * @brief A class for saving the token.
         */
        class Token {
        public:
            enum TokenID {
                // Operators

                Assigment,
                Compare,
                OpenBracket,
                CloseBracket,
                Function,
                Var,

                // Other

                String,
                KeyWord,
            };

        private:
            /**
             * @brief Token name.
             */
            std::string name;

            /**
             * @brief Token id.
             */
            TokenID id;

        public:
            /**
             * @brief A constructor that automatically determines the id for the token.
             * 
             * @param word - token name.
             */
            Token(std::string &word);

            /**
             * @brief A constructor that sets the name and id for the token.
             *
             * @param name - token name.
             * @param id - token id.
             */
            Token(const std::string &name, const TokenID &id);

            /**
             * @brief Returns a token name.
             * 
             * @return A token name.
             */
            const std::string &getName() const noexcept;

            /**
             * @brief Returns a token id.
             * 
             * @return A token id.
             */
            const TokenID &getId() const noexcept;
        };

        using vec_tokens = std::pair<std::vector<Token>, std::string>;
        using vec_tokens_rows = std::vector<std::pair<std::vector<Token>, std::string>>;

    private:
        /**
         * @brief Rows from build file.
         */
        static std::vector<std::string> build_file_rows;

        /**
         * @brief Tokens of rows from build file.
         */
        static vec_tokens tokens;

        /**
         * @brief Tokens from build file.
         */
        static vec_tokens_rows tokens_rows;

        /**
         * @brief Splitting of the build file by rows.
         *
         * @param build_file - the build file.
         */
        static void splitByRows(std::ifstream &build_file);

        /**
         * @brief Splitting of the build_file_rows by tokens.
         */
        static void splitByTokens();

    public:
        /**
         * @brief Returns a vector of tokens rows of a build file.
         *
         * @param build_file - the build file.
         *
         * @return tokens_rows.
         */
        static vec_tokens_rows getTokens(std::ifstream &build_file);
    };
} // namespace sob
