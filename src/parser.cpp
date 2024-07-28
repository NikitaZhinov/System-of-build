#include "parser.h"

#include <stack>

namespace sob {
    void Parser::setError(const std::string &row, std::size_t row_number, const std::string &text) {
        error_code->set(Syntax, std::format("Syntax error! {} on the {} line:\n"
                                            "{}",
                                            text,
                                            row_number,
                                            row));
    }

    std::vector<Lexer::Token> Parser::toPolishNotaion(const Lexer::pair_vec_tokens_string &row, std::size_t &row_number) {
        std::vector<Lexer::Token> res;
        std::stack<Lexer::Token> tokens_stack;

        const std::map<std::string, int> OPERATORS = {
            {  "(", -1},
            {  ")", -1},
            { "or",  0},
            {"and",  1},
            { "==",  2},
            { "!=",  2},
            {  "$",  3},
        };

        for (auto token_it = row.first.begin() + 1; token_it != row.first.end(); token_it++) {
            const Lexer::Token &token = *token_it;
            const Lexer::Token::TokenID &token_id = token.getId();
            if (token_id == Lexer::Token::Var) {
                res.push_back(Lexer::Token((token_it + 1)->getName(), Lexer::Token::Var));
                token_it++;
            } else if (token_id == Lexer::Token::String)
                res.push_back(token);
            else if (token_id == Lexer::Token::OpenBracket)
                tokens_stack.push(token);
            else if (token_id == Lexer::Token::CloseBracket) {
                while (!tokens_stack.empty() && tokens_stack.top().getId() != Lexer::Token::OpenBracket) {
                    res.push_back(tokens_stack.top());
                    tokens_stack.pop();
                }
                if (!tokens_stack.empty())
                    tokens_stack.pop();
            } else if (token_id == Lexer::Token::Compare || token_id == Lexer::Token::KeyWord) {
                int cur_priority = OPERATORS.find(token.getName())->second;
                while (!tokens_stack.empty() && OPERATORS.find(tokens_stack.top().getName())->second >= cur_priority) {
                    res.push_back(tokens_stack.top());
                    tokens_stack.pop();
                }
                tokens_stack.push(token);
            } else {
                setError(row.second, row_number, "Undefined token");
                return res;
            }
        }

        while (!tokens_stack.empty()) {
            res.push_back(tokens_stack.top());
            tokens_stack.pop();
        }

        return res;
    }

    bool Parser::parsCondition(const Lexer::pair_vec_tokens_string &row, std::size_t &row_number) {
        auto polish_row = toPolishNotaion(row, row_number);

        if (error_code->id != OK)
            return false;

        std::stack<std::string> res;

        for (Lexer::Token &token : polish_row) {
            const Lexer::Token::TokenID &token_id = token.getId();
            if (token_id == Lexer::Token::Var)
                res.push(build_class->getVariableValue(token.getName()));
            else if (token_id == Lexer::Token::String)
                res.push(token.getName());
            else if (token_id == Lexer::Token::Compare) {
                const std::string &token_name = token.getName();

                std::string str1 = res.top();
                res.pop();
                std::string str2 = res.top();
                res.pop();

                if (token_name == "==")
                    res.push(str1 == str2 ? "1" : "0");
                else if (token_name == "!=")
                    res.push(str1 != str2 ? "1" : "0");
                else {
                    setError(row.second, row_number, "Undefined operator");
                    return false;
                }
            } else if (token_id == Lexer::Token::KeyWord) {
                const std::string &token_name = token.getName();

                std::string str1 = res.top();
                res.pop();
                std::string str2 = res.top();
                res.pop();

                if (token_name == "or")
                    res.push(str1 == "1" || str2 == "1" ? "1" : "0");
                else if (token_name == "and")
                    res.push(str1 == "1" && str2 == "1" ? "1" : "0");
                else {
                    setError(row.second, row_number, "Undefined operator");
                    return false;
                }
            } else {
                setError(row.second, row_number, "Undefined token");
                return false;
            }
        }

        if (res.size() == 1) {
            if (res.top() == "1")
                return true;
            else
                return false;
        }

        setError(row.second, row_number, "Are you dumb? Or are you just pretending?");
        return false;
    }

    void Parser::parsConditionalConstruction(Lexer::vec_tokens_rows::const_iterator &row, std::size_t &row_number) {
        if (error_code->id != OK)
            return;

        std::string first = row->first.begin()->getName();

        auto parsIf = [&]() {
            parsRow(row, row_number);
            row++;
            row_number++;
            first = row->first.begin()->getName();
        };

        auto passIf = [&]() {
            row++;
            row_number++;
            first = row->first.begin()->getName();
        };

        if (parsCondition(*row, row_number)) {
            passIf();

            while (first != "elif" && first != "else" && first != "endif")
                parsIf();

            while (first != "endif")
                passIf();
        } else {
            while (first != "elif" && first != "else" && first != "endif")
                passIf();

            if (first == "elif")
                parsConditionalConstruction(row, row_number);
            else if (first == "else") {
                passIf();
                while (first != "endif")
                    parsIf();
            }
        }
    }

    bool Parser::parsRow(Lexer::vec_tokens_rows::const_iterator &row, std::size_t &row_number) {
        if (error_code->id != OK)
            return true;

        if (row->first.empty())
            return false;

        auto first_elem = row->first.begin();
        int first_elem_id = first_elem->getId();

        if (first_elem_id == Lexer::Token::String) {
            if (first_elem + 1 == row->first.end()) {
                setError(row->second, row_number, "Undefined token");
                return true;
            }

            if ((first_elem + 1)->getId() == Lexer::Token::Assigment)
                build_class->addVaribale(first_elem->getName(), (first_elem + 2)->getName());
            else if ((first_elem + 1)->getId() == Lexer::Token::Function) {
                if (first_elem + 2 == row->first.end()) {
                    setError(row->second, row_number, "Expected argument");
                    return true;
                }

                const std::string &name = first_elem->getName();
                std::string first_param = (first_elem + 2)->getName();

                if ((first_elem + 2)->getId() == Lexer::Token::Var) {
                    if (first_elem + 3 == row->first.end()) {
                        setError(row->second, row_number, "Expected variable name");
                        return true;
                    }

                    first_param = build_class->getVariableValue((first_elem + 3)->getName());
                }

                if (name == "set_build_folder")
                    build_class->setVariable("BUILD_FOLDER", first_param);
                else if (name == "set_c_standart")
                    build_class->setVariable("C_STANDART", first_param);
                else if (name == "set_cpp_standart")
                    build_class->setVariable("CPP_STANDART", first_param);
                else if (name == "set_debug_mode")
                    build_class->setVariable("DEBUG_MODE", first_param);
                else if (name == "set_c_compiler")
                    build_class->setVariable("C_COMPILER", first_param);
                else if (name == "set_cpp_compiler")
                    build_class->setVariable("CPP_COMPILER", first_param);
                else if (name == "add_executable") {
                    build_class->addExecutable(first_param);
                    auto elem = first_elem + 3;

                    if (elem + 1 == row->first.end()) {
                        setError(row->second, row_number, "Expected more arguments");
                        return true;
                    }

                    while (++elem != row->first.end()) {
                        std::string src_name = elem->getName();
                        if (elem->getId() == Lexer::Token::Var)
                            src_name = build_class->getVariableValue((++elem)->getName());
                        build_class->addSrc(first_param, src_name);
                    }
                }
            } else {
                setError(row->second, row_number, "Expected `=`");
                return true;
            }
        } else if (first_elem_id == Lexer::Token::KeyWord) {
            if (first_elem + 1 == row->first.end()) {
                setError(row->second, row_number, "Expected condition");
                return true;
            }

            if (first_elem->getName() == "if")
                parsConditionalConstruction(row, row_number);
            else {
                setError(row->second, row_number, "Undefined token");
                return true;
            }
        } else {
            setError(row->second, row_number, "Undefined token");
            return true;
        }

        row_number++;
        return false;
    }

    Parser::Parser(const Lexer::vec_tokens_rows &tokens, Build *build_class, Error *error_code) : tokens(tokens), build_class(build_class), error_code(error_code) {}

    void Parser::parsTokens() {
        std::size_t row_number = 1;
        for (auto row = tokens.begin(); row != tokens.end(); row++)
            if (parsRow(row, row_number))
                break;
    }
} // namespace sob
