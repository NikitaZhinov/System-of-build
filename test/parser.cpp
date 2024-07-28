#include "test.h"

#include <gtest/gtest.h>
#include <print>

namespace sob {
    std::vector<Lexer::Token> Test::parser_toPolishNotaion(const Lexer::pair_vec_tokens_string &row, std::size_t &row_number) {
        Error e;
        Build b(&e);
        Parser p(Lexer::vec_tokens_rows(), &b, &e);
        return p.toPolishNotaion(row, row_number);
    }

    bool Test::parser_parsCondition(const Lexer::pair_vec_tokens_string &row, std::size_t &row_number) {
        Error e;
        Build b(&e);
        Parser p(Lexer::vec_tokens_rows(), &b, &e);
        return p.parsCondition(row, row_number);
    }

    sob::Build::var_t Test::parser_parsRow(const sob::Build::var_t &vars, const Lexer::vec_tokens_rows &rows, std::size_t &row_number) {
        Error e;
        Build b(&e);
        b.variables = vars;
        Parser p(Lexer::vec_tokens_rows(), &b, &e);
        auto row = rows.cbegin();
        p.parsRow(row, row_number);
        return b.variables;
    }

    sob::Build::var_t Test::parser_parsConditionalConstruction(const sob::Build::var_t &vars, const Lexer::vec_tokens_rows &rows, std::size_t &row_number) {
        Error e;
        Build b(&e);
        b.variables = vars;
        Parser p(Lexer::vec_tokens_rows(), &b, &e);
        auto row = rows.cbegin();
        p.parsConditionalConstruction(row, row_number);
        return b.variables;
    }
} // namespace sob

TEST(parser, toPolishNotaion) {
    sob::Test t;

    auto in_value = sob::Lexer::pair_vec_tokens_string({ sob::Lexer::Token("if"),
                                                         sob::Lexer::Token("("),
                                                         sob::Lexer::Token("$"),
                                                         sob::Lexer::Token("SYSTEM"),
                                                         sob::Lexer::Token("=="),
                                                         sob::Lexer::Token("LINUX"),
                                                         sob::Lexer::Token("or"),
                                                         sob::Lexer::Token("$"),
                                                         sob::Lexer::Token("SYSTEM"),
                                                         sob::Lexer::Token("=="),
                                                         sob::Lexer::Token("APPLE"),
                                                         sob::Lexer::Token(")"),
                                                         sob::Lexer::Token("and"),
                                                         sob::Lexer::Token("$"),
                                                         sob::Lexer::Token("SYSTEM"),
                                                         sob::Lexer::Token("!="),
                                                         sob::Lexer::Token("WINDOWS") },
                                                       "if ($SYSTEM == LINUX or $SYSTEM == APPLE) and $SYSTEM != WINDOWS");
    std::size_t row_number = 0;

    std::vector<sob::Lexer::Token> ex_value = {
        sob::Lexer::Token("SYSTEM", sob::Lexer::Token::Var),
        sob::Lexer::Token("LINUX"),
        sob::Lexer::Token("=="),
        sob::Lexer::Token("SYSTEM", sob::Lexer::Token::Var),
        sob::Lexer::Token("APPLE"),
        sob::Lexer::Token("=="),
        sob::Lexer::Token("or"),
        sob::Lexer::Token("SYSTEM", sob::Lexer::Token::Var),
        sob::Lexer::Token("WINDOWS"),
        sob::Lexer::Token("!="),
        sob::Lexer::Token("and")
    };

    std::vector<sob::Lexer::Token> out_value = t.parser_toPolishNotaion(in_value, row_number);

    EXPECT_EQ(out_value.size(), ex_value.size());
    for (std::size_t i = 0; i < out_value.size(); i++) {
        auto out_elem = out_value.at(i);
        auto ex_elem = ex_value.at(i);

        if (out_elem != ex_elem) {
            std::println("{} != {}", out_elem.getName(), ex_elem.getName());
            std::println("i = {}", i);
        }

        EXPECT_EQ(out_elem == ex_elem, true);
    }
}

TEST(parser, parsCondition) {
    sob::Test t;

    auto in_value = sob::Lexer::pair_vec_tokens_string({ sob::Lexer::Token("if"),
                                                         sob::Lexer::Token("("),
                                                         sob::Lexer::Token("$"),
                                                         sob::Lexer::Token("SYSTEM"),
                                                         sob::Lexer::Token("=="),
                                                         sob::Lexer::Token("LINUX"),
                                                         sob::Lexer::Token("or"),
                                                         sob::Lexer::Token("$"),
                                                         sob::Lexer::Token("SYSTEM"),
                                                         sob::Lexer::Token("=="),
                                                         sob::Lexer::Token("APPLE"),
                                                         sob::Lexer::Token(")"),
                                                         sob::Lexer::Token("and"),
                                                         sob::Lexer::Token("$"),
                                                         sob::Lexer::Token("SYSTEM"),
                                                         sob::Lexer::Token("!="),
                                                         sob::Lexer::Token("WINDOWS") },
                                                       "if ($SYSTEM == LINUX or $SYSTEM == APPLE) and $SYSTEM != WINDOWS");
    std::size_t row_number = 0;

    bool ex_value =
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WIN64__)
        false
#else
        true
#endif
        ;

    bool out_value = t.parser_parsCondition(in_value, row_number);

    EXPECT_EQ(out_value, ex_value);
}

TEST(parser, parsRow_1) {
    sob::Test t;

    sob::Lexer::vec_tokens_rows in_value = {
        {{ sob::Lexer::Token("TARGET"), sob::Lexer::Token("="), sob::Lexer::Token("kuku") }, "TARGET = kuku"}
    };
    std::size_t row_number = 1;

    sob::Build::var_t ex_value = {
        {"TARGET", "kuku"}
    };

    auto out_value = t.parser_parsRow(sob::Build::var_t(), in_value, row_number);

    EXPECT_EQ(out_value, ex_value);
}

TEST(parser, parsRow_2) {
    sob::Test t;

    sob::Lexer::vec_tokens_rows in_value = {
        {{ sob::Lexer::Token("set_c_compiler"), sob::Lexer::Token(":"), sob::Lexer::Token("gcc") }, "set_c_compiler: gcc"}
    };
    std::size_t row_number = 1;

    sob::Build::var_t ex_value = {
        {"C_COMPILER", "gcc"}
    };

    auto out_value = t.parser_parsRow(sob::Build::var_t({
                                          {"C_COMPILER", "clang"}
    }),
                                      in_value,
                                      row_number);

    EXPECT_EQ(out_value, ex_value);
}

TEST(parser, parsConditionalConstruction) {
    sob::Test t;

    sob::Lexer::vec_tokens_rows in_value = {
        {{ sob::Lexer::Token("if"), sob::Lexer::Token("$"), sob::Lexer::Token("SYSTEM"), sob::Lexer::Token("=="), sob::Lexer::Token("WINDOWS") },     "if $SYSTEM == WINDOWS"},
        {                                             { sob::Lexer::Token("set_c_compiler"), sob::Lexer::Token(":"), sob::Lexer::Token("msvc") },      "set_c_compiler: msvc"},
        {                                           { sob::Lexer::Token("set_cpp_compiler"), sob::Lexer::Token(":"), sob::Lexer::Token("msvc") },    "set_cpp_compiler: msvc"},
        {                                                                                                          { sob::Lexer::Token("else") },                      "else"},
        {                                            { sob::Lexer::Token("set_c_compiler"), sob::Lexer::Token(":"), sob::Lexer::Token("clang") },     "set_c_compiler: clang"},
        {                                        { sob::Lexer::Token("set_cpp_compiler"), sob::Lexer::Token(":"), sob::Lexer::Token("clang++") }, "set_cpp_compiler: clang++"},
        {                                                                                                         { sob::Lexer::Token("endif") },                     "endif"},
    };
    std::size_t row_number = 1;

    sob::Build::var_t ex_value = {
        {      "SYSTEM",   "LINUX"},
        {  "C_COMPILER",   "clang"},
        {"CPP_COMPILER", "clang++"}
    };

    auto out_value = t.parser_parsConditionalConstruction(sob::Build::var_t({
                                                              {      "SYSTEM", "LINUX"},
                                                              {  "C_COMPILER",   "gcc"},
                                                              {"CPP_COMPILER",   "g++"}
    }),
                                                          in_value,
                                                          row_number);

    EXPECT_EQ(out_value, ex_value);
}
