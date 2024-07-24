#pragma once

#include <string>

namespace sob {
    /**
     * @brief Enumeration of error codes.
     */
    enum Error_id {
        OK,
        InvalidInputArgument,
        FileNotFound,
        Syntax,
        BuildError,
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
         * @brief Error text.
         * If the id is not OK, this text is displayed on the screen.
         */
        std::string text;

        /**
         * @brief Default constructor.
         * The variable id is equal to OK
         * and the variable text is equal to "The build was completed successfully.".
         */
        Error();

        /**
         * @brief Sets id and text.
         *
         * @param id - new id.
         * @param text - new text.
         */
        void set(const Error_id &id, const std::string &text);
    };
} // namespace sob
