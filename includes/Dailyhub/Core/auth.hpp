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

namespace Dailyhub {
namespace Core {
typedef struct {
  bool success;
  std::string username;
} Auth_Response;

namespace AuthManager {
  std::string generateJWT(const std::string& username);
  Auth_Response verifyJWT(const std::string& token);
};
};
};

#endif
