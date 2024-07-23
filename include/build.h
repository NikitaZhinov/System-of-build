#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>

namespace sob {
    class Build {
    public:
        using var_t = std::map<std::string, std::string>;
        using exe_t = std::map<std::string, std::set<std::string>>;

    private:
        var_t variables;
        exe_t executables;

    public:
        Build();

        void build(); // TODO
        void addVaribale(const std::string &name, const std::string &value);
        void addExecutable(const std::string &name);
        void addSrc(const std::string &name, const std::string &src_file);
        
        void setVariable(const std::string &name, const std::string &new_value);

        const std::string &getVariableValue(const std::string &name);
    };
} // namespace sob
