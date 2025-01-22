#include "server.hpp"
#include <cstdlib>

crow::SimpleApp Servidor::app = NULL;

void Servidor::Routes() {
  CROW_ROUTE(Servidor::app, "/")([]() {
    return "Hello World!";
  });

  CROW_ROUTE(Servidor::app, "/api/test")([]() {
    return "API Test";
  });

  CROW_ROUTE(Servidor::app, "/api/user/profile/<int>")([](int id) {
    return "User Profile: " + std::to_string(id);
  });
}

void Servidor::Start(uint32_t port) {
  Servidor::app.port(port).run();
  Servidor::Routes();
}

void Servidor::Stop()  {
  Servidor::app.stop();
}

