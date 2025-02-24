#include "Dailyhub/Core/server.hpp"
#include <cstdlib>

crow::SimpleApp Dailyhub::Core::Servidor::app = NULL;
bool running = false;
std::thread server_worker;

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

void Dailyhub::Core::Servidor::Routes() {
  CROW_ROUTE(Servidor::app, "/isonline").methods(crow::HTTPMethod::GET)(isonline);
  CROW_ROUTE(Servidor::app, "/api/login").methods(crow::HTTPMethod::POST)(loginUser);
  CROW_ROUTE(Servidor::app, "/app/register").methods(crow::HTTPMethod::POST)(registerUser);
}

void Dailyhub::Core::Servidor::start_server() {
  const auto GetPort = []() {
    return std::atoi(Dailyhub::Core::DotEnv::get("PORT_SERVER", "7845").c_str());
  };
  auto server_future = Servidor::app.bindaddr("0.0.0.0").port(GetPort()).run_async();
  server_future.wait();
  running = true;
}

void Dailyhub::Core::Servidor::Start() {
  Servidor::Routes();
  server_worker = std::thread(start_server);
}

void Dailyhub::Core::Servidor::Stop()  {
  if (running) {
    Servidor::app.stop();
    server_worker.join();
  }
}

