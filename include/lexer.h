#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace sob {
    /**
     * @brief Static class.
     * Splits text of build file by tokens.
     */
    class Lexer {
    public:
        static const std::vector<std::string> KEY_WORDS;
        static const std::vector<std::string> FUNCTIONS;

        /**
         * @brief A class for saving the token.
         */
        class Token {
            enum TokenID {
                // Operators
                Args,
                Assigment,
                GetVar,
                Compare,

                // Other
                String,
                KeyWord,
                Function,
            };

            std::string name;
            TokenID id;

        public:
            Token(std::string &word);
        };

    private:
        /**
         * @brief A string with all operator characters.
         */
        static const std::string OPERATOR_CHARS;

        /**
         * @brief A string with all paired operator characters.
         */
        static const std::string PAIRED_OPERATOR_CHARS;

        /**
         * @brief Rows from build file.
         */
        static std::vector<std::string> build_file_rows;

        /**
         * @brief Tokens from build file.
         */
        static std::vector<Token> tokens;

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
         * @brief Returns a vector of tokens of a build file.
         * 
         * @param build_file - the build file.
         * 
         * @return A vector of tokens.
         */
        static std::vector<Token> getTokens(std::ifstream &build_file);
    };
} // namespace sob
