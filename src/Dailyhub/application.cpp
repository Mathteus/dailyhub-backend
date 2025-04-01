#include "Dailyhub/application.hpp"

using namespace Dailyhub::Core;
using namespace Dailyhub::Schemas;

const std::string path_env{"/media/henrique/A/dailyhub-backend/.env"};

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
    body_json["html"] = Utility::readFile(Dailyhub::Core::DotEnv::get("PATH_EMAIL", ""), replacements);

    auto res = cli.Post("/emails", headers, body_json.dump(), "application/json");
    if (res->status == 200) {
      spdlog::info("Email enviado com sucesso para {}\n", user.email);
    }
    spdlog::error("Error ao enviar email: {}\n", user.email);
  } catch(std::exception& e) {
    spdlog::error("Erro ao Enviar email: {}\n", e.what());
  }
}

Dailyhub::Application::ResturnApplication Dailyhub::Application::Register(nlohmann::json user_json) {
  using User_Register = Dailyhub::Schemas::Users::DTO_USER_REGISTER;
  const User_Register user = Dailyhub::Schemas::Users::Parse_DTO_User_Register(user_json);
  Dailyhub::Application::ResturnApplication response;

  const auto email = [user]() {
    Dailyhub::Schemas::Users::User_Register_Email user_email = {user.name, user.code, {"Registro Dailyhub"}, user.email};
    Dailyhub::Application::Send_Email(user_email);
  };

  try {
    const auto hash{PasswordHasher::to_hash_pass(user.password)};
    if (!hash.success && !hash.data) {
      response.code = 400;
      response.message = hash.error;
      response.success = false;
    }

    const auto response_from_users{Dailyhub::Users::CreateUser(user.name, user.tag, user.email, hash.data->data())};
    if (response_from_users.success) {
      spdlog::info("Usuário cadastrado com sucesso.\n");
      // email();
      response.code = 201;
      response.success = false;
    } else {
      std::cout << response_from_users.error->c_str() << '\n';
      std::string error{response_from_users.error->data()};
      spdlog::error("Erro ao cadastrar usuário: {}\n", error);
      response.code = 400;
      response.message = error;
      response.success = false;
    }
  } catch (const std::exception& e) {
    spdlog::error("Error no servidor: {}\n", e.what());
    response.code = 500;
    response.message = e.what();
    response.success = false;
  }

  return response;
}

Dailyhub::Application::ResturnApplication Dailyhub::Application::Login(std::string user, std::string password) {
  Dailyhub::Application::ResturnApplication response;

  try {
    const auto hash_password{};
    PasswordHasher::to_hash_pass();
    const auto response_from_users{Dailyhub::Users::()};
  } catch (const std::exception& e) {
    spdlog::error("Error hashing password: {}\n", e.what());
    response.code = 500;
    response.message = e.what();
    response.success = false;
  }

  return response;
}

Dailyhub::Application::Application() {
  Dailyhub::Core::DotEnv::load(path_env.c_str());
  if (Dailyhub::Core::DataBase::connect()) {
    std::function<void(crow::SimpleApp& app)> func{Dailyhub::Routes::Configure};
    if (Dailyhub::Core::Servidor::Start(func)) {
      spdlog::info("Aplicação está rodando http://localhost:7845 !!");
    } else {
      spdlog::error("banco de dados iniciou, mas servidor não");
    }
  }
}

Dailyhub::Application::~Application() {
  Dailyhub::Core::Servidor::Stop();
  Dailyhub::Core::DataBase::close();
  spdlog::info("Aplicação foi encerrada!");
}
