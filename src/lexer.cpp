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

    void Lexer::Token::defineID() {
        if (name == "=")
            id = Assigment;
        else if (name == "==" || name == "!=")
            id = Compare;
        else if (name == "(")
            id = OpenBracket;
        else if (name == ")")
            id = CloseBracket;
        else if (name == ":")
            id = Function;
        else if (name == "$")
            id = Var;
        else {
            for (const std::string &key_word : KEY_WORDS) {
                if (key_word == name) {
                    id = KeyWord;
                    break;
                }
            }
        }
    }

    Lexer::Token::Token(const std::string &word) : name(word), id(String) {
        defineID();
    }

    Lexer::Token::Token(std::string &&word) : Token(word) {
        word.clear();
    }

    Lexer::Token::Token(const std::string &name, const TokenID &id) : name(name), id(id) {}

    const std::string &Lexer::Token::getName() const noexcept {
        return name;
    }

    const Lexer::Token::TokenID &Lexer::Token::getId() const noexcept {
        return id;
    }

    Lexer::vec_tokens Lexer::tokens;
    Lexer::vec_tokens_rows Lexer::tokens_rows;

    void Lexer::splitByRows(std::ifstream &build_file) {
        while (!build_file.eof()) {
            std::string row;
            std::getline(build_file, row);
            tokens_rows.push_back(std::pair<std::vector<Token>, std::string>(std::vector<Token>(), row));
        }
    }

    void Lexer::splitByTokens() {
        auto pushWord = [&](std::string &word) {
            if (!word.empty())
                tokens.push_back(std::move(word));
        };

        for (auto &tokens_row : tokens_rows) {
            std::string &row = tokens_row.second;
            std::string word;

            bool is_str = false;
            bool is_char = false;
            for (char &c : row) {
                if (c == '"' && !is_char) {
                    is_str = !is_str;
                    if (!is_str)
                        pushWord(word);
                    continue;
                } else if (c == '\'' && !is_str) {
                    is_char = !is_char;
                    if (!is_char)
                        pushWord(word);
                    continue;
                } else if ((c == ' ' || c == '\t') && !is_str && !is_char) {
                    pushWord(word);
                    continue;
                }

                if (is_str || is_char) {
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

            tokens_row.first = tokens;
            tokens.clear();
        }
    }

    Lexer::vec_tokens_rows Lexer::getTokens(std::ifstream &build_file) {
        splitByRows(build_file);
        splitByTokens();

        return tokens_rows;
    }
} // namespace sob
