#include "sob.h"

#include "lexer.h"
#include "parser.h"

#include <cstring>
#include <print>
#include <filesystem>

namespace sob {
    void SOB::setPathToSobFile() {
        path_to_sob_file = default_name_file;
    }

    void SOB::setPathToSobFile(const char *path) {
        std::filesystem::path s = path;
        if (s.extension().string() == default_name_file)
            path_to_sob_file = path;
        else if (std::filesystem::is_directory(s))
            path_to_sob_file = s.string() + "/" + default_name_file;
    }

    void SOB::parsInputArgs(int argc, const char **argv) { // TODO flags support
        switch (argc) {
            case 1:
                setPathToSobFile();
                break;

            case 2:
                setPathToSobFile(argv[1]);
                break;
        }
    }

    void SOB::openBuildFile() {
        if (error_code.id != OK)
            return;

        build_file.open(path_to_sob_file);
        if (!build_file.is_open())
            error_code.set(FileNotFound, std::format("File {} doesn`t exist!", path_to_sob_file));
    }

    void SOB::parsBuildFile() {
        if (error_code.id != OK)
            return;

        Parser p(Lexer::getTokens(build_file), &b, &error_code);
        p.parsTokens();
    }

    SOB::SOB() : default_name_file(".sob"), b(&error_code) {}

    SOB::SOB(const std::string &defalt_name) : default_name_file(defalt_name), b(&error_code) {}

    Error_id SOB::run(int argc, const char **argv) {
        parsInputArgs(argc, argv);
        openBuildFile();
        parsBuildFile();

        b.build();

        std::println("{}", error_code.text); // Prints the error text.
        return error_code.id;
    }
} // namespace sob
