#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "../core/database.hpp"
#include "../core/server.hpp"
#include "../core/utility.hpp"
#include "../core/hash-password.hpp"
#include "../core/httplib.h"

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <sstream>

namespace Dailyhub {
  class Application {
  public: 
    Application();
    ~Application();
  };

  nlohmann::json Login(std::string user, std::string password);
  nlohmann::json Register(std::string user, std::string password, std::string email);
  nlohmann::json SendEmail(std::string email);
};

#endif