export module operators;

import common;

export namespace sob {
    Errors assignment(Variable &var, const std::string &val) {
        var.value = val;
        return OK;
    }
} // namespace sob
