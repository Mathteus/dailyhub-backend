#include "Dailyhub/application.hpp"

using namespace Dailyhub::Core;

// nlohmann::json Dailyhub::Application::Login(std::string user, std::string password) {

// }

void Dailyhub::Application::Send_Email(const Dailyhub::Schemas::Users::User_Register_Email& user) {
  const auto authBearer = []() {
    return std::string("Bearer: " + DotEnv::get("SECRET_KEY_EMAIL", ""));
  };

  try {
    httplib::Client cli{"https://api.resend.com"};
    httplib::Headers headers = {
      {"Authorization", authBearer()},
      {"Content-Type", "application/json"}
    };

    const std::unordered_map<std::string, std::string> replacements{{
      {"USERNAME", user.name},
      {"CODE", user.code},
      {"MESSAGE_TEXT", user.message}
    }};

    nlohmann::json body_json;
    body_json["from"] = "Acme <onboarding@resend.dev>";
    body_json["to"] = nlohmann::json::array({ user.email });
    body_json["subject"] = "Registro na Dailyhub";
    body_json["html"] = Dailyhub::Core::Utility::readHTML("../../mail/index", replacements);

    auto res = cli.Post("/emails", headers, body_json.dump(), "application/json");
    if (res->status == 200) {
      spdlog::info("Email enviado com sucesso para {}\n", user.email);
    }
    spdlog::error("Error ao enviar email: {}\n", user.email);
  } catch(std::exception& e) {
    spdlog::error("Erro ao Enviar email: {}\n", e.what());
  }
}

nlohmann::json Dailyhub::Application::Register(nlohmann::json user_json) {
  using User_Register_Email = Dailyhub::Schemas::Users::User_Register_Email;
  nlohmann::json res_json;

  const auto email = [user_json]() {
    User_Register_Email user;
    user.name = user_json["username"];
    user.code = user_json["code"];
    user.message = "Registro Dailyhub";
    user.email = user_json["email"];
    Dailyhub::Application::Send_Email(user);
  };

  try {
    const auto hash{PasswordHasher::to_hash_pass(user_json["password"])};
    if (!hash.success && !hash.data) {
      return {
        {"status", 400},
        {"message", hash.error->data()}
      };
    }

    auto response{Dailyhub::Users::CreateUser(user_json["username"], user_json["tag"], user_json["email"], hash.data->data())};
    if (response.success) {
        spdlog::info("Usuário cadastrado com sucesso.\n");
        email();
        return {
          {"status", 201},
          {"message", ""}
        };
    }

    spdlog::error("Erro ao cadastrar usuário: {}\n", response.error->data());
    res_json = {
      {"status", 400},
      {"message", response.error->data()}
    };
  } catch (const std::exception& e) {
    spdlog::error("Error hashing password: {}\n", e.what());
    res_json = {
      {"status", 500},
      {"message", e.what()}
    };
  }

  return res_json;
}

Dailyhub::Application::Application() {
  Dailyhub::Core::DotEnv::load(".env");
  // if (Dailyhub::Core::DataBase::connect()) {
  //   Dailyhub::Core::Servidor::Start();
  // }

  spdlog::info("Application running!");
}

Dailyhub::Application::~Application() {
  // Dailyhub::Core::Servidor::Stop();
  // Dailyhub::Core::DataBase::close();
  spdlog::info("Application closing!");
}
