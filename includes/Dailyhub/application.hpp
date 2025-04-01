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
#include "Core/dotenv.hpp"
#include "schemas.hpp"
#include "users.hpp"
#include "routes.hpp"

#include <iostream>
#include <string>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <sstream>
#include <unordered_map>
#include <regex>
#include <fstream>
#include <iomanip>

namespace Dailyhub {
class Application {
public:
  Application();
  ~Application();

  using ResturnApplication = Dailyhub::Core::Errors::ResponseServer;

  static ResturnApplication Login(std::string user, std::string password);
  static ResturnApplication Register(nlohmann::json user);
  static void Send_Email(const Dailyhub::Schemas::Users::User_Register_Email& user_json);
};
};

#endif // DAILYHUB_APPLICATION_HPP
