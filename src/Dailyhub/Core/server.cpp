#include "Dailyhub/Core/server.hpp"
#include <cstdlib>

crow::SimpleApp Servidor::app = NULL;
std::thread Servidor::server_worker;
bool Servidor::running = false;

bool verifyKeyApi(const crow::request& apikey) {
  return std::string(std::getenv("X_API_KEY")) == apikey.get_header_value("x-api-key");
}

crow::response isonline(const crow::request& req) {
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
    const nlohmann::json register_user = Dailyhub::Register_On_Database(nlohmann::json::parse(req.body));
    const uint32_t code = Utility::Integer(register_user["status"]);
    return crow::response(code, register_user["message"]);
  }

  return crow::response(401);
}

void Servidor::Routes() {
  CROW_ROUTE(Servidor::app, "/isonline").methods(crow::HTTPMethod::GET)(isonline);
  CROW_ROUTE(Servidor::app, "/api/login").methods(crow::HTTPMethod::GET)(loginUser);
  CROW_ROUTE(Servidor::app, "/app/register").methods(crow::HTTPMethod::GET)(registerUser);
}

void Servidor::start_server() {
  auto server_future = Servidor::app.bindaddr("0.0.0.0").port(7845).run_async();
  server_future.wait();
  running = true;
}

void Servidor::Start() {
  Servidor::Routes();
  Servidor::server_worker = std::thread(start_server);
}

void Servidor::Stop()  {
  if (running) {
    Servidor::app.stop();
    Servidor::server_worker.join();
  }
}

