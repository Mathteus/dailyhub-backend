#ifndef DAILYHUB_ERROR_HANDLER_HPP
#define DAILYHUB_ERROR_HANDLER_HPP

#include <string>
#include <optional>

namespace Dailyhub {
namespace Core {
namespace Errors {
    template<typename TypeError> struct Response {
        bool success;
        std::optional<TypeError> data;
        std::optional<std::string> error;
    };

    using ResponseBoolean = struct Response<bool>;
    using ResponseString = struct Response<std::string>;
    using ResponseVoid = struct Response<void>;
    using ResponseShort = struct Response<uint16_t>;
};
};
};

#endif
