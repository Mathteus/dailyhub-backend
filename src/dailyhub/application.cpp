#include "application.hpp"

nlohmann::json Dailyhub::Register(std::string user, std::string password, std::string email) {
  try {
    const auto [hash, salt] = PasswordHasher::to_hash_pass(password);
    std::stringstream ss{};
    ss << "INSERT INTO users (hash, salt, username, email) VALUES ('" << hash << "', '" << salt << "', '" << user << "', '"  << email << "');";
    
    const auto response = DataBase::executeQuery(ss.str());
    if (response.status) {
      spdlog::info("Usuário cadastrado com sucesso.");
      DataBase::cleanResult(response.result);
      return {
        {"status", 200},
        {"message", ""}
      };
    }
    spdlog::error("Erro ao cadastrar usuário. ");
    return {
      {"status", 200},
      {"message", response.error}
    };
  } catch (const std::exception& e) {
    spdlog::error("Error hashing password: {}", e.what());
    return {
      {"status", 500},
      {"message", e.what()}
    };
  }
}

Dailyhub::Application::Application() {
  if (DataBase::connect()) {
    std::string sqlFile{Utility::readFilesSQL("../database/nanoid")};
    DataBase::executeQuery(sqlFile);
    sqlFile = Utility::readFilesSQL("../database/commands");
    DataBase::executeQuery(sqlFile);
    Servidor::Start();
  }
}

Dailyhub::Application::~Application() {
  Servidor::Stop();
  DataBase::close();
}
