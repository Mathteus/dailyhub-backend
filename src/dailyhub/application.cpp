#include "application.hpp"

DailyHub::DailyHub() {
  PostgreSQLConnector::connect();
  Servidor::Start();
}

DailyHub::~DailyHub() {
  Servidor::Stop();
  PostgreSQLConnector::close();
}

void DailyHub::run() {
  spdlog::info("Running APP..");
}
