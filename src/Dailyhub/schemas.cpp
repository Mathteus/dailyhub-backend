#include "Dailyhub/schemas.hpp"

using namespace Dailyhub::Schemas;
using namespace Dailyhub::Core;

Users::DTO_User Users::perseUser(const nlohmann::json& j) {
  using User = Users::DTO_User;
  User p;
  p.user_id = j.at("user_id").get<std::string>();
  p.hash = j.at("hash").get<std::string>();
  p.name = j.at("name").get<std::string>();
  p.tag = j.at("tag").get<std::string>();
  p.email = j.at("email").get<std::string>();

  std::string last_login_str = j.at("last_login").get<std::string>();
  p.last_login = Utility::parse_date_time(last_login_str);

  std::string created_at_str = j.at("created_at").get<std::string>();
  p.created_at = Utility::parse_date_time(created_at_str);
  return p;
}

Users::DTO_USER_LOGIN Users::Parse_DTO_Login(const nlohmann::json& j) {
  using User = Users::DTO_USER_LOGIN;
  User p;
  p.user_id = j[0]["user_id"].get<std::string>();
  p.email = j[0]["email"].get<std::string>();
  p.name = j[0]["name"].get<std::string>();
  p.tag = j[0]["tag"].get<std::string>();
  p.hash = j[0]["hash"].get<std::string>();
  return p;
}

Users::DTO_USER_REGISTER Users::Parse_DTO_User_Register(const nlohmann::json& j) {
  using User = Users::DTO_USER_REGISTER;
  User p;

  p.code = j[0]["code"].get<std::string>();
  p.email = j[0]["email"].get<std::string>();
  p.name = j[0]["name"].get<std::string>();
  p.tag = j[0]["tag"].get<std::string>();
  p.password = j[0]["password"].get<std::string>();
  p.message = j[0]["message"].get<std::string>();

  return p;
}

nlohmann::json Users::DTO_User_Register_To_JSON(const Users::DTO_USER_REGISTER& user) {
  nlohmann::json j;
  j["code"] = user.code;
  j["email"] = user.email;
  j["name"] = user.name;
  j["tag"] = user.tag;
  j["password"] = user.password;
  j["message"] = user.message;
  return j;
}
