#include "database.hpp"

#include <cstdlib> // Para std::getenv
#include <sstream> // Para std::ostringstream

PGconn* DataBase::conn_ = nullptr;

bool DataBase::connect() {
  std::string url{std::getenv("URL_POSTGRES")};
  if (isConnected()) {
    spdlog::warn("Conexão já está estabelecida.");
    return true;
  }

  conn_ = PQconnectdb(url.c_str());
  if (PQstatus(conn_) == CONNECTION_OK) {
    spdlog::info("Conexão com o banco de dados estabelecida.");
    return true;
  } else {
    spdlog::error("Falha ao conectar no banco de dados: {}", PQerrorMessage(conn_));
    PQfinish(conn_);
    conn_ = nullptr;
    return false;
  }
}

void DataBase::close() {
  if (conn_ != nullptr) {
    PQfinish(conn_);
    conn_ = nullptr;
    spdlog::info("Conexão com o banco de dados fechada.");
  }
}

bool DataBase::isConnected() {
  return conn_ != nullptr && PQstatus(conn_) == CONNECTION_OK;
}

ResponseDatabase DataBase::executeQuery(const std::string& query) {
  ResponseDatabase response;
  if (!isConnected()) {
  spdlog::error("Não há conexão com o banco de dados para executar a query.");
    response.status = false;
    response.error = "Não há conexão com o banco de dados para executar a query.";
    return response;
  }

  PGresult* res = PQexec(conn_, query.c_str());
  if(PQresultStatus(res) != PGRES_TUPLES_OK && PQresultStatus(res) != PGRES_COMMAND_OK) {
    std::string error{PQerrorMessage(conn_)};
    spdlog::error("Erro ao executar a query: {}", error);
    PQclear(res);
    response.status = false;
    response.error = error;
    return response;
  }

  response.status = true;
  response.result = res;
  return response;
}

void DataBase::cleanResult(PGresult* res) {
  PQclear(res);
}

void DataBase::DisplayQueryResult(PGresult* res) {
  if (PQntuples(res) == 0) {
    std::cout << "No results found.\n";
    return;
  }

  int cols = PQnfields(res);
  for (int col = 0; col < cols; ++col) {
    std::cout << std::setw(15) << std::left << PQfname(res, col);
  }

  std::cout << '\n';
  for (int col = 0; col < cols; ++col) {
    std::cout << std::setw(15) << std::left << "----------------";
  }

  std::cout << '\n';

  int rows = PQntuples(res);
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      if (PQgetisnull(res, row, col)) {
        std::cout << std::setw(15) << std::left << "(null)";
        } else {
        std::cout << std::setw(15) << std::left << PQgetvalue(res, row, col);
      }
    }
    std::cout << '\n';
  }
  PQclear(res);
}

nlohmann::json DataBase::resultToJson(PGresult* res) {
  nlohmann::json j;
  if (PQntuples(res) == 0) {
    PQclear(res);
    return j;
  }
    
  int cols = PQnfields(res);
  std::vector<std::string> column_names;
  for (int col = 0; col < cols; ++col) {
    column_names.push_back(PQfname(res,col));
  }
    
  int rows = PQntuples(res);
  for (int row = 0; row < rows; ++row) {
    nlohmann::json row_json;
    for (size_t col = 0; col < column_names.size(); ++col) {
      if(PQgetisnull(res, row, col)){
        row_json[column_names[col]] = nullptr;
      } else {
        row_json[column_names[col]] = PQgetvalue(res, row, col);
      }
    }
    j.push_back(row_json);
  }
  PQclear(res);
  return j;
}