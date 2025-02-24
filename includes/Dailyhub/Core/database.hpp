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
#include "Dailyhub/Core/dotenv.hpp"
#include "Dailyhub/Core/error_handler.hpp"

namespace Dailyhub {
namespace Core {
class DataBase {
private:
  using ResponsePGresult = struct Dailyhub::Core::Errors::Response<PGresult*>;
  static PGconn* conn_;
  static std::string sanitizeString(const std::string& input);
  static ResponsePGresult executeQueryRaw(const std::string& query);
  static nlohmann::json resultToJson(PGresult* res);
  static void initWithSQLFiles();

public:
  typedef struct {
    uint8_t colums;
    const char* const* params;
  } ParamsQuery;

  using ResponseJson = struct Dailyhub::Core::Errors::Response<nlohmann::json>;

  DataBase() = delete;
  ~DataBase() = delete;

  static bool connect();
  static void close();
  static bool isConnected();
  static Dailyhub::Core::Errors::ResponseBoolean execQuery(const char* query, ParamsQuery params_query);
  static ResponseJson Select(const char* query, ParamsQuery params_query);
};
};
};

#endif
