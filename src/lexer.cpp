#include "lexer.h"

namespace sob {
    const std::set<std::string> Lexer::KEY_WORDS = {
        "if",
        "elif",
        "else",
        "endif",
        "and",
        "or",
    };

    const std::string Lexer::OPERATOR_CHARS = "=()!$:";
    const std::string Lexer::PAIRED_OPERATOR_CHARS = "=!";

    Lexer::Token::Token(std::string &word) : name(word), id(String) {
        if (word == "=")
            id = Assigment;
        else if (word == "==" || word == "!=")
            id = Compare;
        else if (word == "(")
            id = OpenBracket;
        else if (word == ")")
            id = CloseBracket;
        else if (word == ":")
            id = Function;
        else if (word == "$")
            id = Var;
        else {
            for (const std::string &key_word : KEY_WORDS) {
                if (key_word == word) {
                    id = KeyWord;
                    break;
                }
            }
        }

        word.clear();
    }

    Lexer::Token::Token(const std::string &name, const TokenID &id) : name(name), id(id) {}

    const std::string &Lexer::Token::getName() const noexcept {
        return name;
    }

    const Lexer::Token::TokenID &Lexer::Token::getId() const noexcept {
        return id;
    }

    std::vector<std::string> Lexer::build_file_rows;
    Lexer::vec_tokens Lexer::tokens;
    Lexer::vec_tokens_rows Lexer::tokens_rows;

    void Lexer::splitByRows(std::ifstream &build_file) {
        while (!build_file.eof()) {
            std::string row;
            std::getline(build_file, row);
            build_file_rows.push_back(row);
        }
    }

    void Lexer::splitByTokens() {
        auto pushWord = [&](std::string &word) {
            if (!word.empty())
                tokens.first.push_back(word);
        };

        for (std::string &row : build_file_rows) {
            std::string word;

            bool is_str = false;
            for (char &c : row) {
                if (c == '"' || c == '\'') {
                    is_str = !is_str;
                    if (!is_str)
                        pushWord(word);
                    continue;
                } else if (c == ' ' || c == '\t') {
                    pushWord(word);
                    continue;
                }

                if (is_str) {
                    word.push_back(c);
                    continue;
                }

                if (word.empty())
                    word.push_back(c);
                else {
                    char &last_char = *(word.end() - 1);
                    if (PAIRED_OPERATOR_CHARS.find(last_char) != std::string::npos &&
                        PAIRED_OPERATOR_CHARS.find(c) != std::string::npos)
                        word.push_back(c);
                    else if (OPERATOR_CHARS.find(c) != std::string::npos) {
                        pushWord(word);
                        word.push_back(c);
                    } else if (OPERATOR_CHARS.find(c) == std::string::npos &&
                               OPERATOR_CHARS.find(last_char) != std::string::npos) {
                        pushWord(word);
                        word.push_back(c);
                    } else
                        word.push_back(c);
                }
            }

            pushWord(word);

            tokens.second = row;
            tokens_rows.push_back(tokens);
            tokens.first.clear();
        }
    }

    Lexer::vec_tokens_rows Lexer::getTokens(std::ifstream &build_file) {
        splitByRows(build_file);
        splitByTokens();

        return tokens_rows;
    }
} // namespace sob
