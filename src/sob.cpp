#include "sob.h"

#include <print>

namespace sob {
    constexpr Error::Error() : id(OK), text("The build was completed successfully.") {}

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
        for (int i = 1; i <= 4; i++)
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

    void SOB::printError() {
        std::print("{}", error_code.text);
    }

    constexpr SOB::SOB() : default_name_file(".sob") {}

    constexpr SOB::SOB(const std::string &defalt_name) : default_name_file(defalt_name) {}

    Error_id SOB::run(int argc, const char **argv) {
        parsInputArgs(argc, argv);

        printError();
        return error_code.id;
    }
} // namespace sob
