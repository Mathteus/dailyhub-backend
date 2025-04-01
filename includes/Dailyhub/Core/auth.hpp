#ifndef DAILYHUB_AUTH_HPP
#define DAILYHUB_AUTH_HPP

#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <jwt-cpp/jwt.h>
#include <sstream>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include "Dailyhub/Core/error_handler.hpp"

namespace Dailyhub {
namespace Core {
namespace AuthManager {
  std::string generateJWT(const std::string& username);
  Dailyhub::Core::Errors::ResponseString verifyJWT(const std::string& token);
};
};
};

#endif
