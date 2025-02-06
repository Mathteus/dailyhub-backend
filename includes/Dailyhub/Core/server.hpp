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
  static void Routes();
  static std::thread server_worker;
  static void start_server();
  static bool running;

public:
  Servidor() = default;
  ~Servidor() = default;

  static void Start();
  static void Stop();
};
};
};

#endif
