#pragma once

#include "build.h"
#include "error.h"

#include <fstream>
#include <string>
#include <vector>

namespace sob {
    class Test;

    /**
     * @brief Class SOB.
     * Starts the build using the run method.
     */
    class SOB {
        friend Test;

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
         * @brief Build file.
         */
        std::ifstream build_file;

        /**
         * @brief A build class.
         * Filled in by the parser.
         * Then it starts the build.
         */
        Build b;

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
         * @brief Parses the input arguments.
         *
         * @param argc - the number of arguments.
         * @param argv - an array of arguments.
         */
        void parsInputArgs(int argc, const char **argv);

        /**
         * @brief Opens the build file.
         */
        void openBuildFile();

        /**
         * @brief Parses the build file.
         */
        void parsBuildFile();

    public:
        /**
         * @brief Default constructor.
         * The variable default_name_file is equal to ".sob".
         */
        SOB();

        /**
         * @brief Sets default name of build file.
         *
         * @param defalt_path - default name of build file.
         */
        SOB(const std::string &defalt_name);

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
