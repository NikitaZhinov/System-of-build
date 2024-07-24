#include "build.h"

#include <filesystem>

namespace fs = std::filesystem;

namespace sob {
    Build::Build(Error *error_code) : error_code(error_code),
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WIN64__)
                                      variables({
                                          { "SYSTEM", "WINDOWS" },
                                              { "C_COMPILER", "msvc" },
                                              { "CPP_COMPILER", "msvc" },
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

    void Build::build() {
        if (error_code->id != OK)
            return;

        if (getVariableValue("C_COMPILER") == "msvc" || getVariableValue("CPP_COMPILER") == "msvc") {
            error_code->set(BuildError, std::format("The SoB does not yet support this compiler (msvc)."));
            return;
        }

        bool build_dir_is_exist = false;
        const fs::path &build_path = getVariableValue("BUILD_FOLDER");
        for (const auto &entry : fs::directory_iterator(".")) {
            if (entry.is_directory() && fs::absolute(entry.path()) == fs::absolute(build_path)) {
                build_dir_is_exist = true;
                break;
            }
        }
        if (!build_dir_is_exist)
            system(("mkdir " + build_path.string()).c_str());

        const std::string &c_compiler = getVariableValue("C_COMPILER");
        const std::string &c_standart = getVariableValue("C_STANDART");
        const std::string &cpp_compiler = getVariableValue("CPP_COMPILER");
        const std::string &cpp_standart = getVariableValue("CPP_STANDART");
        std::string debug_mode = getVariableValue("DEBUG_MODE") == "On" ? "-g" : "";

        for (auto exe : executables) {
            std::string compiler = c_compiler;
            std::string standart = "c" + c_standart;
            int err = 0;

            for (const std::string &src_file : exe.second) {
                if (fs::path(src_file).extension() != ".c") {
                    compiler = cpp_compiler;
                    standart = "c++" + cpp_standart;
                    break;
                }
            }

            std::set<std::string> objs;
            std::string cmd = std::format("{} -std={} {} -o {} ", compiler, standart, debug_mode, build_path.string() + "/" + exe.first);

            for (const std::string &src_file : exe.second) {
                std::string obj = build_path.string() + "/" + fs::path(src_file).filename().string() + ".o";
                err = system(std::format("{} -std={} {} -c {} -o {}", compiler, standart, debug_mode, src_file, obj).c_str());
                if (err)
                    break;
                cmd += obj;
            }

            if (err)
                continue;

            system(cmd.c_str());
        }
    }

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
