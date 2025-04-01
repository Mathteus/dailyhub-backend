#include "Dailyhub/Core/server.hpp"
#include <cstdlib>

crow::SimpleApp Dailyhub::Core::Servidor::app = NULL;
bool running = false;
std::thread server_worker;

void Dailyhub::Core::Servidor::Routes(std::function<void(crow::SimpleApp& app)>& func) {
  func(Servidor::app);
}

void Dailyhub::Core::Servidor::start_server() {
  const auto GetPort = []() {
    return std::atoi(Dailyhub::Core::DotEnv::get("PORT_SERVER", "7845").c_str());
  };
  auto server_future = Servidor::app.bindaddr("0.0.0.0").port(GetPort()).run_async();
  server_future.wait();
}

bool Dailyhub::Core::Servidor::Start(std::function<void(crow::SimpleApp& app)>& func) {
  if (running) {
    spdlog::error("Servidor já Iniciado!");
    return false;
  }

  Servidor::Routes(func);
  server_worker = std::thread(start_server);
  running = true;
  return true;
}

bool Dailyhub::Core::Servidor::Stop()  {
  if (running) {
    Servidor::app.stop();
    server_worker.join();
    return true;
  }

  spdlog::error("Servidor Não Iniciado!");
  return false;
}

