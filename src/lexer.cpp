#include "lexer.h"

namespace sob {
    const std::vector<std::string> Lexer::KEY_WORDS = {
        "if",
        "then",
        "elif",
        "else",
        "endif",
    };

    const std::vector<std::string> Lexer::FUNCTIONS = {
        "set_build_folder",
        "set_c_standart",
        "set_cpp_standart",
        "set_debug_mode",
        "add_executable",
    };

    Lexer::Token::Token(std::string &word) : name(word), id(String) {
        if (word == ":")
            id = Args;
        else if (word == "=")
            id = Assigment;
        else if (word == "$")
            id = GetVar;
        else if (word == "==")
            id = Compare;
        else {
            for (const std::string &key_word : KEY_WORDS) {
                if (key_word == word) {
                    id = KeyWord;
                    break;
                }
            }
            if (id == String) {
                for (const std::string &func : FUNCTIONS) {
                    if (func == word) {
                        id = Function;
                        break;
                    }
                }
            }
        }

        word.clear();
    }

    const std::string Lexer::OPERATOR_CHARS = "=:$";
    const std::string Lexer::PAIRED_OPERATOR_CHARS = "=";

    void Lexer::splitByRows(std::ifstream &build_file) {
        while (!build_file.eof()) {
            std::string row;
            std::getline(build_file, row);
            build_file_rows.push_back(row);
        }
    }

    void Lexer::splitByTokens() {
        for (std::string &row : build_file_rows) {
            std::string word;

            bool is_str = false;
            for (char &c : row) {
                if (c == '"' || c == '\'') {
                    is_str = !is_str;
                    if (!is_str)
                        tokens.push_back(word);
                    continue;
                } else if (c == ' ' || c == '\t') {
                    if (!word.empty())
                        tokens.push_back(word);
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
                        tokens.push_back(word);
                        word.push_back(c);
                    } else
                        word.push_back(c);
                }
            }
        }
    }

    std::vector<Lexer::Token> Lexer::getTokens(std::ifstream &build_file) {
        splitByRows(build_file);
        splitByTokens();

        return tokens;
    }
} // namespace sob
