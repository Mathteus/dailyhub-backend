#include "Dailyhub/routes.hpp"
#include <cstdlib>

bool verifyKeyApi(const crow::request& apikey) {
  return std::string(Dailyhub::Core::DotEnv::get("X_API_KEY", "ERROR")) == apikey.get_header_value("x-api-key");
}

crow::response isonline() {
  return crow::response(200, "OK");
}

crow::response loginUser(const crow::request& req) {
  if (verifyKeyApi(req)) {
    return crow::response(200, "Login My APP");
  }
  return crow::response(401);
}

crow::response registerUser(const crow::request& req) {
  if (verifyKeyApi(req)) {
    const nlohmann::json register_user = Dailyhub::Application::Register(nlohmann::json::parse(req.body));
    const uint16_t code = Dailyhub::Core::Utility::Integer(register_user["status"]);
    return crow::response(code, register_user["message"]);
  }
  return crow::response(401);
}

void Dailyhub::Routes::Configure(const crow::SimpleApp& server_application) const {
  CROW_ROUTE(server_application, "/isonline").methods(crow::HTTPMethod::GET)(isonline);
  CROW_ROUTE(server_application, "/api/v1/login").methods(crow::HTTPMethod::POST)(loginUser);
  CROW_ROUTE(server_application, "/api/v1/register").methods(crow::HTTPMethod::POST)(registerUser);
}