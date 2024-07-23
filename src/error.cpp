#include "error.h"

namespace sob {
    Error::Error() : id(OK), text("The build was completed successfully.") {}

    void Error::set(const Error_id &id, const std::string &text) {
        this->id = id;
        this->text = text;
    }
} // namespace sob
