#include "database.hpp"

PGconn* PostgreSQLConnector::conn_ = nullptr;

void PostgreSQLConnector::connect() {
  std::string url{std::getenv("URL_POSTGRES")};

  try {
    PostgreSQLConnector::conn_ = PQconnectdb(url.c_str());
    if (PQstatus(PostgreSQLConnector::conn_) != CONNECTION_OK) {
      std::string error_msg = "Connection Error: " + std::string(PQerrorMessage(PostgreSQLConnector::conn_));
      PQfinish(PostgreSQLConnector::conn_);
      conn_ = nullptr;
      throw std::runtime_error(error_msg);
    }
  } catch(std::exception& e) {
    spdlog::error("Error connecting to PostgreSQL: {}", e.what());
  }
}

void PostgreSQLConnector::close() {
  if (PostgreSQLConnector::conn_) {
    PQfinish(PostgreSQLConnector::conn_);
  }

  delete PostgreSQLConnector::conn_;
}

bool PostgreSQLConnector::isConnected() {
  return PQstatus(PostgreSQLConnector::conn_) == CONNECTION_OK;
}

PGresult* PostgreSQLConnector::executeQuery(const std::string& query) {
  try {
    if (!isConnected()) {
      throw std::runtime_error("Connection not available, unable to execute query");
    }

    PGresult* result = PQexec(PostgreSQLConnector::conn_, query.c_str());
    if (PQresultStatus(result) != PGRES_TUPLES_OK && PQresultStatus(result) != PGRES_COMMAND_OK) {
      std::string error_msg = "Query Error: " + std::string(PQerrorMessage(PostgreSQLConnector::conn_));
      PQclear(result);
      throw std::runtime_error(error_msg);
    }
    return result;
  } catch(std::exception& e) {
    spdlog::error("Error executeQuery PostgreSQL: {}", e.what());
    return nullptr;
  }
}

void PostgreSQLConnector::clearResult(PGresult* result) {
  if(result) {
    PQclear(result);
  }
}

void PostgreSQLConnector::DisplayQueryResult(PGresult* res) {
  // Pega o número de linhas e colunas
  int rows = PQntuples(res);
  int cols = PQnfields(res);

  // Exibe os nomes das colunas
  for(int col = 0; col < cols; col++){
    std::cout << std::setw(15) << std::left << PQfname(res, col); // Define o tamanho da coluna
  }

  std::cout << std::endl;
  for(int col = 0; col < cols; col++){
    std::cout << std::setw(15) << std::left << "----------------"; // Separador
  }
  std::cout << std::endl;

  // Exibe os dados
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      std::cout << std::setw(15) << std::left << PQgetvalue(res, row, col);
    }
    std::cout << std::endl;
  }
}