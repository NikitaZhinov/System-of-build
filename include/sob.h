#pragma once

#include <string>

namespace sob {
    /**
     * @brief Enumeration of error codes.
     */
    enum Error_id {
        OK = 0,
    };

    /**
     * @brief Error structure.
     */
    struct Error {
        /**
         * @brief error number.
         */
        Error_id id;

        /**
         * @brief Error text. If the id is not OK, this text is displayed on the screen.
         */
        std::string text;

        constexpr Error();
    };

    /**
     * @brief Class SOB. Starts the build using the run method.
     */
    class SOB {
        /**
         * @brief Error code.
         */
        Error error_code;

        /**
         * @brief Default name of build file.
         */
        const std::string default_name_file;

        /**
         * @brief Path to ".sob" file.
         */
        std::string path_to_sob_file;

        /**
         * @brief Parses the input arguments.
         *
         * @param argc - the number of arguments.
         * @param argv - an array of arguments.
         */
        void parsInputArgs(int argc, const char **argv);

        /**
         * @brief Sets the default path to the build file.
         */
        void setPathToSobFile();

        /**
         * @brief Sets the path to the build file.
         *
         * @param path - the path to the assembly file.
         */
        void setPathToSobFile(const char *path);

        /**
         * @brief Prints the error text.
         */
        void printError();

    public:
        /**
         * @brief Default constructor. The variable default_name_file is equal to ".sob".
         */
        constexpr SOB();

        /**
         * @brief Sets default name of build file.
         * 
         * @param defalt_path - default name of build file.
         */
        constexpr SOB(const std::string &defalt_name);

        /**
         * @brief The method of starting the build.
         *
         * @param argc - the number of input arguments of the entry point.
         * @param argv - an array of input arguments of the entry point.
         *
         * @return Error_id - error code.
         */
        Error_id run(int argc, const char **argv);
    };
} // namespace sob
