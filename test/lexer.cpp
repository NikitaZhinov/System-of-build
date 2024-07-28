#include "test.h"

#include <gtest/gtest.h>
#include <print>

namespace sob {
    Lexer::Token::TokenID Test::lexer_Token_defineID(const std::string &word) {
        Lexer::Token t(word);
        return t.getId();
    }

    Lexer::vec_tokens_rows Test::lexer_splitByTokens(const std::vector<std::string> &tokens_rows) {
        for (auto &row : tokens_rows)
            Lexer::tokens_rows.push_back(Lexer::pair_vec_tokens_string(Lexer::vec_tokens(), row));
        Lexer::splitByTokens();
        return Lexer::tokens_rows;
    }
} // namespace sob

TEST(lexer, Token_defineID_1) {
    sob::Test t;

    std::string word = "=";
    sob::Lexer::Token::TokenID ex_id = sob::Lexer::Token::Assigment;

    EXPECT_EQ(t.lexer_Token_defineID(word), ex_id);
}

TEST(lexer, Token_defineID_2) {
    sob::Test t;

    std::string word = "==";
    sob::Lexer::Token::TokenID ex_id = sob::Lexer::Token::Compare;

    EXPECT_EQ(t.lexer_Token_defineID(word), ex_id);
}

TEST(lexer, Token_defineID_3) {
    sob::Test t;

    std::string word = "(";
    sob::Lexer::Token::TokenID ex_id = sob::Lexer::Token::OpenBracket;

    EXPECT_EQ(t.lexer_Token_defineID(word), ex_id);
}

TEST(lexer, Token_defineID_4) {
    sob::Test t;

    std::string word = ")";
    sob::Lexer::Token::TokenID ex_id = sob::Lexer::Token::CloseBracket;

    EXPECT_EQ(t.lexer_Token_defineID(word), ex_id);
}

TEST(lexer, Token_defineID_5) {
    sob::Test t;

    std::string word = ":";
    sob::Lexer::Token::TokenID ex_id = sob::Lexer::Token::Function;

    EXPECT_EQ(t.lexer_Token_defineID(word), ex_id);
}

TEST(lexer, Token_defineID_6) {
    sob::Test t;

    std::string word = "$";
    sob::Lexer::Token::TokenID ex_id = sob::Lexer::Token::Var;

    EXPECT_EQ(t.lexer_Token_defineID(word), ex_id);
}

TEST(lexer, Token_defineID_7) {
    sob::Test t;

    std::string word = "hello";
    sob::Lexer::Token::TokenID ex_id = sob::Lexer::Token::String;

    EXPECT_EQ(t.lexer_Token_defineID(word), ex_id);
}

TEST(lexer, Token_defineID_8) {
    sob::Test t;

    std::string word = "if";
    sob::Lexer::Token::TokenID ex_id = sob::Lexer::Token::KeyWord;

    EXPECT_EQ(t.lexer_Token_defineID(word), ex_id);
}

TEST(lexer, splitByTokens) {
    sob::Test t;

    using Token = sob::Lexer::Token;

    std::vector<std::string> in_value = {
        "TARGET_1 = example1",
        "SRC_1=main1.cpp",
        "",
        "TARGET_2=example2",
        "SRC_2 = main2.cpp",
        "",
        "set_build_folder : build",
        "set_c_standart      :      17",
        "set_cpp_standart: \"23\"",
        "set_debug_mode: \"On\"",
        "",
        "",
        "",
        "if $SYSTEM ==           WINDOWS              and ($SYSTEM!=LINUX)",
        "   set_c_compiler:gcc",
        "   set_cpp_compiler:g++",
        "elif (($SYSTEM != APPLE))",
        "   set_cpp_compiler : \"g++\"",
        "else",
        "   set_cpp_compiler : 'clang++'",
        "endif",
        "",
        "add_executable : $TARGET_1 $SRC_1",
        "add_executable : $TARGET_2 $SRC_2"
    };
    sob::Lexer::vec_tokens_rows ex_value = {
        {                                                                                                                       { Token("TARGET_1"), Token("="), Token("example1") },                                               "TARGET_1 = example1"},
        {                                                                                                                         { Token("SRC_1"), Token("="), Token("main1.cpp") },                                                   "SRC_1=main1.cpp"},
        {                                                                                                                                                       std::vector<Token>(),                                                                  ""},
        {                                                                                                                       { Token("TARGET_2"), Token("="), Token("example2") },                                                 "TARGET_2=example2"},
        {                                                                                                                         { Token("SRC_2"), Token("="), Token("main2.cpp") },                                                 "SRC_2 = main2.cpp"},
        {                                                                                                                                                       std::vector<Token>(),                                                                  ""},
        {                                                                                                                  { Token("set_build_folder"), Token(":"), Token("build") },                                          "set_build_folder : build"},
        {                                                                                                                       { Token("set_c_standart"), Token(":"), Token("17") },                                     "set_c_standart      :      17"},
        {                                                                                                                     { Token("set_cpp_standart"), Token(":"), Token("23") },                                          "set_cpp_standart: \"23\""},
        {                                                                                                                       { Token("set_debug_mode"), Token(":"), Token("On") },                                            "set_debug_mode: \"On\""},
        {                                                                                                                                                       std::vector<Token>(),                                                                  ""},
        {                                                                                                                                                       std::vector<Token>(),                                                                  ""},
        {                                                                                                                                                       std::vector<Token>(),                                                                  ""},
        {{ Token("if"), Token("$"), Token("SYSTEM"), Token("=="), Token("WINDOWS"), Token("and"), Token("("), Token("$"), Token("SYSTEM"), Token("!="), Token("LINUX"), Token(")") }, "if $SYSTEM ==           WINDOWS              and ($SYSTEM!=LINUX)"},
        {                                                                                                                      { Token("set_c_compiler"), Token(":"), Token("gcc") },                                             "   set_c_compiler:gcc"},
        {                                                                                                                    { Token("set_cpp_compiler"), Token(":"), Token("g++") },                                           "   set_cpp_compiler:g++"},
        {                                                { Token("elif"), Token("("), Token("("), Token("$"), Token("SYSTEM"), Token("!="), Token("APPLE"), Token(")"), Token(")") },                                         "elif (($SYSTEM != APPLE))"},
        {                                                                                                                    { Token("set_cpp_compiler"), Token(":"), Token("g++") },                                     "   set_cpp_compiler : \"g++\""},
        {                                                                                                                                                          { Token("else") },                                                              "else"},
        {                                                                                                                { Token("set_cpp_compiler"), Token(":"), Token("clang++") },                                   "   set_cpp_compiler : 'clang++'"},
        {                                                                                                                                                         { Token("endif") },                                                             "endif"},
        {                                                                                                                                                       std::vector<Token>(),                                                                  ""},
        {                                                                         { Token("add_executable"), Token(":"), Token("$"), Token("TARGET_1"), Token("$"), Token("SRC_1") },                                 "add_executable : $TARGET_1 $SRC_1"},
        {                                                                         { Token("add_executable"), Token(":"), Token("$"), Token("TARGET_2"), Token("$"), Token("SRC_2") },                                 "add_executable : $TARGET_2 $SRC_2"}
    };

    sob::Lexer::vec_tokens_rows out_value = t.lexer_splitByTokens(in_value);

    EXPECT_EQ(out_value.size(), ex_value.size());
    for (std::size_t i = 0; i < out_value.size(); i++) {
        auto out_elem = out_value.at(i);
        auto ex_elem = ex_value.at(i);

        EXPECT_EQ(out_elem.first.size(), ex_elem.first.size());
        for (std::size_t j = 0; j < out_elem.first.size(); j++) {
            auto out_elem_first = out_elem.first.at(j);
            auto ex_elem_first = ex_elem.first.at(j);

            if (out_elem_first != ex_elem_first) {
                std::println("{} != {}", out_elem_first.getName(), ex_elem_first.getName());
                std::println("i = {}, j = {}", i, j);
            }

            EXPECT_EQ(out_elem_first == ex_elem_first, true);
        }

        EXPECT_EQ(out_elem.second, ex_elem.second);
    }
}
