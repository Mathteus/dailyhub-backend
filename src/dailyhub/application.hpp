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
#include <unordered_map>
#include <regex>
#include <fstream>

typedef struct {
  std::string name;
  std::string code;
  std::string message;
  std::string email;
} User_Register_Email;

namespace Dailyhub {
  class Application {
  public: 
    Application();
    ~Application();
  };

  nlohmann::json Login_On_Database(std::string user, std::string password);
  nlohmann::json Register_On_Database(std::string user, std::string password, std::string email);
  nlohmann::json Send_Email(const User_Register_Email& user);
};

#endif