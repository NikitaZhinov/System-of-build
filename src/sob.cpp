#include "../include/sob.h"

Error Sob::error_code = OK;
std::string Sob::path_to_buildfile = ".sob";
std::ifstream Sob::file;
std::vector<std::string> Sob::code;

void Sob::parsInputParametrs(int argc, const char **argv) {
    if (error_code != OK)
        return;

    switch (argc) {
        case 1:
            break;

        case 2:
            path_to_buildfile = argv[1];
            break;

        default:
            error_code = Invalid_input_parametrs;
            break;
    }
}

void Sob::getFile() {
    if (error_code != OK)
        return;

    file.open(path_to_buildfile);
    if (!file.is_open())
        error_code = File_not_found;
}

void Sob::parsFile() {
    if (error_code != OK)
        return;

    error_code = Parser::parsFile(file);
}

Error Sob::run(int argc, const char **argv) {
    parsInputParametrs(argc, argv); // parsing input parametrs
    getFile();                      // get buildfile
    parsFile();                     // parsing buildfile

    return error_code;
}
