#include "application.hpp"

bool DailyHub::Register(std::string user, std::string password, std::string email) {
  const auto [hash, salt] = PasswordHasher::to_hash_pass(password);
  // try {
  // } catch (const std::exception& e) {
  //   spdlog::error("Error hashing password: {}", e.what());
  //   return false;
  // }

  std::stringstream ss;
  ss << "INSERT INTO users (hash, salt, username, email) VALUES ('" << hash << "', '" << salt << "', '" << user << "', '"  << email << "');";
  
  PGresult* result = PostgreSQLConnector::executeQuery(ss.str());
  if (result) {
    PostgreSQLConnector::clearResult(result);
    spdlog::info("User registered successfully");
    return true;
  } else {
    spdlog::error("Error registering user");
    return false;
  }
}

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
  // try {
  //   httplib::Client cli("https://api.restful-api.dev");
  //   auto res = cli.Get("/objects");
  //   if (res->status == httplib::StatusCode::OK_200) {
  //     std::cout << res->body << std::endl;
  //   }
  // } catch(std::exception& e) {
  //   auto err = e.what();
  //   spdlog::error("Request failed: {}", err);
  // }
}
