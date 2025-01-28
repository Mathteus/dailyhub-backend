#ifndef SERVER_HPP
#define SERVER_HPP

#include <crow.h>
#include "dotenv.h"
#include <cstdlib>
#include <string>
#include <future>
#include <thread>

class Servidor {
private:
  static crow::SimpleApp app;
  static void Routes();
  static std::thread server_worker;
  static void start_server();

public:
  Servidor() = default;
  ~Servidor() = default;

  static void Start();
  static void Stop();
};

#endif
