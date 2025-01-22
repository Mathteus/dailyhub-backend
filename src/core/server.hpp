#ifndef SERVER_HPP
#define SERVER_HPP

#include "crow.h"

class Servidor {
private:
  static crow::SimpleApp app;
  static void Routes();

public:
  Servidor() = default;
  ~Servidor() = default;

  static void Start(uint32_t port);
  static void Stop();
};

#endif
