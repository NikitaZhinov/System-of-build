#pragma once

#include "error.h"

#include <map>
#include <set>
#include <string>
#include <vector>

namespace sob {
    class Test;

    /**
     * @brief A build class for the build itself.
     */
    class Build {
        friend Test;

    public:
        using var_t = std::map<std::string, std::string>;
        using exe_t = std::map<std::string, std::set<std::string>>;

    private:
        /**
         * @brief A pointer to the error_code from SOB class.
         */
        Error *error_code;

        /**
         * @brief All variables for the build.
         */
        var_t variables;

        /**
         * @brief All executables for the build.
         */
        exe_t executables;

    public:
        /**
         * @brief A constructor that defines some variables.
         */
        Build(Error *error_code);

        /**
         * @brief Starts a build.
         */
        void build();

        /**
         * @brief Adds a new variable or defines an exist variable.
         *
         * @param name - the name for the new variable or the name of an exist variable.
         * @param value - the value for a variable.
         */
        void addVaribale(const std::string &name, const std::string &value);

        /**
         * @brief Adds a new executable.
         *
         * @param name - the name for a new executable.
         */
        void addExecutable(const std::string &name);

        /**
         * @brief Adds the source file for an executable.
         *
         * @param name - the name of an executable.
         * @param src_file - the source file for an executable.
         */
        void addSrc(const std::string &name, const std::string &src_file);

        /**
         * @brief Sets the new value for the exist variable.
         *
         * @param name - the name of a variable.
         * @param new_value - the new value for a variable.
         */
        void setVariable(const std::string &name, const std::string &new_value);

        /**
         * @brief Returns a value of a variable.
         *
         * @param name - the name of a variable.
         *
         * @return A value of a variable.
         */
        const std::string &getVariableValue(const std::string &name);
    };
} // namespace sob
