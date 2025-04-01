#include "Dailyhub/users.hpp"

Response_Register Dailyhub::Users::CreateUser(std::string username, std::string tag, std::string email, std::string hash) {
  Response_Register response;
  if (hash.empty()) {
    response.success = false;
    response.data = std::nullopt;
    response.error = "hash ou salt da senha está vazia!";
    return response;
  }

  if (username.empty()) {
    response.success = false;
    response.data = std::nullopt;
    response.error = "Está faltando username!";
    return response;
  }

  if (tag.empty()) {
    response.success = false;
    response.data = std::nullopt;
    response.error = "Está faltando tag!";
    return response;
  }

  if (email.empty()) {
    response.success = false;
    response.data = std::nullopt;
    response.error = "Está faltando email!";
    return response;
  }

  if (Dailyhub::Core::Utility::IsValidEmail(email)) {
    response.success = false;
    response.data = std::nullopt;
    response.error = "Email inválido!";
    return response;
  }

  if (Dailyhub::Core::Utility::ContainsSymbols(username)) {
    response.success = false;
    response.data = std::nullopt;
    response.error = "O username não pode conter simbolos!";
    return response;
  }

  if (Dailyhub::Core::Utility::ContainsSymbols(tag)) {
    response.success = false;
    response.data = std::nullopt;
    response.error = "A tag não pode conter simbolos!";
    return response;
  }

  Dailyhub::Core::DataBase::ParamsQuery params;
  const char* const ptrArray[] = {hash.c_str(), username.c_str(), tag.c_str(), email.c_str()};
  params.colums = 4;
  params.params = ptrArray;
  auto response_DB{Dailyhub::Core::DataBase::execQuery("INSERT INTO users (hash, name, tag, email) VALUES ($1, $2, $3, $4);", params)};
  response.success = response_DB.success;
  response.error = response.error;
  response.data = response_DB.data;
  return response;
}

Response_UserLogin Dailyhub::Users::VerifyUser(std::string& data_user, std::string type) {
  Response_UserLogin response;
  if (data_user.empty() && type.empty()) {
    response.success = false;
    response.data = std::nullopt;
    response.error = "necessario email ou username para logar!";
    return response;
  }

  const auto TO_DTO = [](std::optional<nlohmann::json>& j) {
    return (j)
      ? std::optional<DTO_USER_LOGIN>(Parse_DTO_Login(j))
      : std::optional<DTO_USER_LOGIN>(std::nullopt);
  };

  if (type == "EMAIL") {
    if (Dailyhub::Core::Utility::IsValidEmail(data_user)) {
      response.success = false;
      response.data = std::nullopt;
      response.error = "O Email está em formato inválido!";
      return response;
    }

    Dailyhub::Core::DataBase::ParamsQuery params;
    const char* const ptrArray[] = {data_user.c_str()};
    params.colums = 1;
    params.params = ptrArray;
    auto response_DB{Dailyhub::Core::DataBase::Select("SELECT hash, user_id, name, tag FROM users WHERE email ILIKE $1;", params)};
    response.success = response_DB.success;
    response.error = response.error;
    response.data = TO_DTO(response_DB.data);
  } else if (type == "USERNAME") {
    if (Dailyhub::Core::Utility::ContainsSymbols(data_user)) {
      response.success = false;
      response.data = std::nullopt;
      response.error = "o username não pode conter simbolos!";
      return response;
    }

    Dailyhub::Core::DataBase::ParamsQuery params;
    const char* const ptrArray[] = {data_user.c_str()};
    params.colums = 1;
    params.params = ptrArray;
    auto response_DB{Dailyhub::Core::DataBase::Select("SELECT hash, user_id, name, tag FROM users WHERE tag ILIKE $1;", params)};
    response.success = response_DB.success;
    response.error = response.error;
    response.data = TO_DTO(response_DB.data);
  } else {
    spdlog::error("tipo para verificação da senha inválido!");
    response.success = false;
    response.error = "tipo para verificação da senha inválido!";
    response.data = std::nullopt;
  }

  return response;
}

// Response_GetPassword GetUserInfo(std::string& userid);
// Response_Update UpdateUser(std::string hash="", std::string salt="", std::string username="", std::string email="");
// Response_Delete DeleteUser(std::string& userid);
