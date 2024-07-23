#include "build.h"

namespace sob {
    Build::Build() :
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WIN64__)
                     variables({
                         { "SYSTEM", "WINDOWS" },
                             { "C_COMPILER", "cl.exe" },
                             { "CPP_COMPILER", "cl.exe" },
#elif defined(__linux__)
                     variables({
                         { "SYSTEM", "LINUX" },
                             { "C_COMPILER", "gcc" },
                             { "CPP_COMPILER", "g++" },
#elif defined(__APPLE__)
                     variables({
                         { "SYSTEM", "APPLE" },
                         { "C_COMPILER", "clang" },
                         { "CPP_COMPILER", "clang++" },
#endif
                             { "BUILD_FOLDER", "." },
                             { "DEBUG_MODE", "Off" },
                             { "C_STANDART", "17" },
                             { "CPP_STANDART", "17" },
                     }) {
    }

    void Build::build() {}

    void Build::addVaribale(const std::string &name, const std::string &value) {
        if (variables.find(name) == variables.end())
            variables.insert({ name, value });
        else
            setVariable(name, value);
    }

    void Build::addExecutable(const std::string &name) {
        executables.insert(std::pair(name, std::set<std::string>()));
    }

    void Build::addSrc(const std::string &name, const std::string &src_file) {
        executables.find(name)->second.insert(src_file);
    }

    void Build::setVariable(const std::string &name, const std::string &new_value) {
        variables.find(name)->second = new_value;
    }

    const std::string &Build::getVariableValue(const std::string &name) {
        return variables.find(name)->second;
    }
} // namespace sob
