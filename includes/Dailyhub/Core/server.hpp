#ifndef DAILYHUB_SERVER_HPP
#define DAILYHUB_SERVER_HPP

#include <crow.h>
#include <cstdlib>
#include <string>
#include <future>
#include <thread>
#include "Dailyhub/application.hpp"

namespace Dailyhub {
namespace Core {
class Servidor {
private:
  static crow::SimpleApp app;
  static void Routes(std::function<void(crow::SimpleApp& app)>& func);
  static void start_server();

public:
  Servidor() = default;
  ~Servidor() = default;

  static void Start(std::function<void(crow::SimpleApp& app)>& func);
  static void Stop();
};
};
};

#endif
