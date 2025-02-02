#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <iostream>
#include <string>
#include <postgresql/libpq-fe.h>
#include <stdexcept>
#include <iomanip>
#include <exception>
#include <spdlog/spdlog.h>
#include <memory>
#include <nlohmann/json.hpp>

typedef struct {
  bool status;
  PGresult* result;
  std::string error;
} ResponseDatabase;


class DataBase {
private:
  static PGconn* conn_;
  static void DisplayQueryResult(PGresult* res);
  static bool isConnected();

public:
  DataBase() = delete;
  ~DataBase() = delete;

  static bool connect();
  static void close();
  static ResponseDatabase executeQuery(const std::string& query);
  static nlohmann::json resultToJson(PGresult* res);
  static void cleanResult(PGresult* res);
};


#endif