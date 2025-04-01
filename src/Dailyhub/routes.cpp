#include "Dailyhub/routes.hpp"
#include <cstdlib>
#include <crow.h>

const uint16_t OK{200};
const uint16_t UNAUTHORIZED{401};

bool verifyFailFromKeyApi(const crow::request& apikey) {
  const std::string API_KEY{Dailyhub::Core::DotEnv::get("X_API_KEY", "ERROR")};
  return API_KEY != apikey.get_header_value("x-api-key");
}

crow::response isonline() {
  return crow::response(OK, "OK");
}

crow::response loginUser(const crow::request& req) {
  if (verifyFailFromKeyApi(req)) {
    return crow::response(UNAUTHORIZED);
  }

  return crow::response(OK, "Login My APP");
}

crow::response registerUser(const crow::request& req) {
  if (verifyFailFromKeyApi(req)) {
    return crow::response(UNAUTHORIZED);
  }

  if (const auto register_user = Dailyhub::Application::Register(nlohmann::json::parse(req.body)); register_user.message) {
    return crow::response(register_user.code, register_user.message->data());
  } else {
    return crow::response(register_user.code);
  }
}

void Dailyhub::Routes::Configure(crow::SimpleApp& server_application) {
  CROW_ROUTE(server_application, "/isonline").methods(crow::HTTPMethod::GET)(isonline);
  CROW_ROUTE(server_application, "/api/v1/login").methods(crow::HTTPMethod::POST)(loginUser);
  CROW_ROUTE(server_application, "/api/v1/register").methods(crow::HTTPMethod::POST)(registerUser);
}
