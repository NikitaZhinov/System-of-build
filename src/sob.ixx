export module SoB;

#include <fstream>
#include <print>
#include <string>
#include <vector>

export namespace sob {
    enum Error {
        OK,
        File_not_found,
        Invalid_input_parametrs,
    };

    class Sob {
        static Error error_code;
        static std::string path_to_buildfile;
        static std::ifstream file;
        static std::vector<std::string> code;

    public:
        static void parsInputParametrs(int argc, const char **argv) {
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

        static void getFile() {
            if (error_code != OK)
                return;

            file.open(path_to_buildfile);
            if (!file.is_open())
                error_code = File_not_found;
        }

        static void parsFile() {
            std::string command;
            char current_symbol = 0;
            while (file.get(current_symbol)) {
                if (current_symbol == ' ' || current_symbol == '\t' || current_symbol == '\n') {
                    
                } else {
                
                }
            }
        }

        static Error run(int argc, const char **argv) {
            parsInputParametrs(argc, argv); // parsing input parametrs
            getFile();                      // get buildfile
            parsFile();                     // prsing buildfile

            return error_code;
        }
    };

    Error Sob::error_code = OK;
    std::string Sob::path_to_buildfile = ".sob";
    std::ifstream Sob::file;
    std::vector<std::string> Sob::code;
} // namespace sob
