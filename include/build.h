#pragma once

#include "error.h"

#include <map>
#include <set>
#include <string>
#include <vector>

namespace sob {
    class Build {
    public:
        using var_t = std::map<std::string, std::string>;
        using exe_t = std::map<std::string, std::set<std::string>>;

    private:
        Error *error_code;

        var_t variables;
        exe_t executables;

    public:
        Build(Error *error_code);

        void build();
        void addVaribale(const std::string &name, const std::string &value);
        void addExecutable(const std::string &name);
        void addSrc(const std::string &name, const std::string &src_file);

        void setVariable(const std::string &name, const std::string &new_value);

        const std::string &getVariableValue(const std::string &name);
    };
} // namespace sob
