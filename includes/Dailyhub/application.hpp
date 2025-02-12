#ifndef DAILYHUB_APPLICATION_HPP
#define DAILYHUB_APPLICATION_HPP
#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <string>
#include <nlohmann/json.hpp>

#include "Core/database.hpp"
#include "Core/server.hpp"
#include "Core/utility.hpp"
#include "Core/hash-password.hpp"
#include "Core/httplib.h"

#include <iostream>
#include <string>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <sstream>
#include <unordered_map>
#include <regex>
#include <fstream>

namespace Dailyhub {
 class Application {
  public: 
    Application();
    ~Application();
  };

  typedef struct {
    std::string name;
    std::string code;
    std::string message;
    std::string email;
  } User_Register_Email;

  nlohmann::json Login_On_Database(std::string user, std::string password);
  nlohmann::json Register_On_Database(nlohmann::json user);
  void Send_Email(const User_Register_Email& user_json);
};

#endif // DAILYHUB_APPLICATION_HPP
