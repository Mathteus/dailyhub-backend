#ifndef DAILYHUB_DATABASE_HPP
#define DAILYHUB_DATABASE_HPP

#include "utility.hpp"
#include <iostream>
#include <string>
#include <postgresql/libpq-fe.h>
#include <stdexcept>
#include <iomanip>
#include <exception>
#include <spdlog/spdlog.h>
#include <memory>
#include <nlohmann/json.hpp>
#include <regex>
#include <cstdlib>
#include <sstream>

namespace Dailyhub {
namespace Core {
typedef struct {
  bool status;
  std::string error;
  nlohmann::json json;
} ResponseDatabase;

class DataBase {
private:
  typedef struct {
    bool status;
    PGresult* result;
    std::string error;
  } Inner_Response;

  static PGconn* conn_;
  static std::string sanitizeString(const std::string& input);
  static Inner_Response executeQuery(const std::string& query);
  static nlohmann::json resultToJson(PGresult* res);
  static void initWithSQLFiles();

public:
  DataBase() = delete;
  ~DataBase() = delete;

  static bool connect();
  static void close();
  static bool isConnected();

  static ResponseDatabase Register_User(const std::string& hash, const std::string& salt, const std::string& username, const std::string& email);
  static ResponseDatabase Login_user(const std::string& user, const std::string& token);
};
};
};

#endif
