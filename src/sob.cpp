#include "sob.h"

#include "lexer.h"
#include "parser.h"

#include <cstring>
#include <print>

namespace sob {
    void SOB::parsInputArgs(int argc, const char **argv) {
        switch (argc) {
            case 1:
                setPathToSobFile();
                break;

            case 2:
                setPathToSobFile(argv[1]);
                break;

            default:
                // TODO flags support
                break;
        }
    }

    void SOB::setPathToSobFile() {
        path_to_sob_file = default_name_file;
    }

    void SOB::setPathToSobFile(const char *path) {
        std::string s;
        for (int i = 4; i > 0; i--)
            s.push_back(path[strlen(path) - i]);
        if (s == default_name_file)
            path_to_sob_file = path;
        else {
            path_to_sob_file = path;
            char last_char = path[strlen(path) - 1];
            if (last_char == '\\' || last_char == '/')
                path_to_sob_file += default_name_file;
            else
                path_to_sob_file += "/" + default_name_file;
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
