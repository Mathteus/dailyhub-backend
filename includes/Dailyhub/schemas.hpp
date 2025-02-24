#ifndef DAILYHUB_SCHEMAS_HPP
#define DAILYHUB_SCHEMAS_HPP

#include <cstdlib>
#include <string>
#include <variant>
#include <map>
#include <nlohmann/json.hpp>
#include "Core/database.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include "date/date.h"
#include "Dailyhub/Core/error_handler.hpp"

using namespace Dailyhub::Core::Errors;

namespace Dailyhub {
namespace Schemas {

namespace Users {
  typedef struct {
    std::string user_id;
    std::string name;
    std::string tag;
    std::string email;
  } DTO_User_Login;

  typedef struct {
    std::string hash;
    std::string email;
  } DTO_GET_PASSWORD;

  typedef struct {
    std::string user_id;
    std::string hash;
    std::string name;
    std::string tag;
    std::string email;
    std::chrono::system_clock::time_point last_login;
    std::chrono::system_clock::time_point created_at;
  } DTO_User;

  typedef struct {
    std::string name;
    std::string code;
    std::string message;
    std::string email;
  } User_Register_Email;

  using Response_Register = struct Response<bool>;
  using Response_UserLogin = struct Response<DTO_User_Login>;
  using Response_GetPassword = struct Response<DTO_GET_PASSWORD>;
  using Response_Update = struct Response<bool>;
  using Response_Delete = struct Response<bool>;
  using Response_UserData = struct Response<DTO_User>;

  DTO_User_Login Parse_DTO_Login(const nlohmann::json& j);
  DTO_User perseUser(const nlohmann::json& j);
};

namespace Kanban {

};

namespace Finance {

};

namespace Blog {

};

};
};

#endif // SCHEMAS_HPP
