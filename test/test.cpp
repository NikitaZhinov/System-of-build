#include "test.h"

bool operator==(const sob::Lexer::Token &a, const sob::Lexer::Token &b) {
    return a.getName() == b.getName() && a.getId() == b.getId();
}
