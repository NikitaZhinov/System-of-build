#include "test.h"

#include <gtest/gtest.h>

namespace sob {
    std::string Test::sob_setPathToSobFile(const char *path) {
        SOB s;
        s.setPathToSobFile(path);
        return s.path_to_sob_file;
    }
} // namespace sob

TEST(sob, setPathToSobFile_1) {
    sob::Test t;
    const char *path = "path/to/.sob";
    EXPECT_EQ(t.sob_setPathToSobFile(path), "path/to/.sob");
}

TEST(sob, setPathToSobFile_2) {
    sob::Test t;
    const char *path = "path/to/";
    EXPECT_EQ(t.sob_setPathToSobFile(path), "path/to/.sob");
}

TEST(sob, setPathToSobFile_3) {
    sob::Test t;
    const char *path = "path/to";
    EXPECT_EQ(t.sob_setPathToSobFile(path), "path/to/.sob");
}

TEST(sob, setPathToSobFile_4) {
    sob::Test t;
    const char *path = ".sob";
    EXPECT_EQ(t.sob_setPathToSobFile(path), ".sob");
}
