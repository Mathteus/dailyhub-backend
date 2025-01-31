#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <iostream>
#include <string>
#include <postgresql/libpq-fe.h>
#include <stdexcept>
#include <iomanip>
#include <exception>
#include <spdlog/spdlog.h>

class PostgreSQLConnector {
private:
  static PGconn* conn_;

public:
  PostgreSQLConnector() = default;
  ~PostgreSQLConnector() = default;

  static void connect();
  static void close();
  static bool isConnected();
  static PGresult* executeQuery(const std::string& query);
  static void clearResult(PGresult* result);
  static void DisplayQueryResult(PGresult* res);
};

#endif