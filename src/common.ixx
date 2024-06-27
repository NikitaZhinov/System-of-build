export module common;

#include <functional>
#include <string>

export namespace sob {
    enum Errors {
        OK = 0,
    };

    struct Variable {
        std::string name;
        std::string value;
    };

    struct Operator {
        std::string sign;
        Errors (*description)(Variable &var, const std::string &val);
    };
} // namespace sob
