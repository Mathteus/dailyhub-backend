#include "application.hpp"

std::string replaceTemplates(std::string html, const std::unordered_map<std::string, std::string>& replacements) {
  if (html.empty() || replacements.empty()) {
    return "";
  }

  std::regex templateRegex{R"(\{\{\s*(\w+)\s*\}\})"};
  std::string result;
  std::sregex_iterator it{html.begin(), html.end(), templateRegex};
  std::sregex_iterator end;
  size_t lastMatchEnd = 0;

  while (it != end) {
    std::smatch match = *it;
    size_t matchPos = match.position();
    result += html.substr(lastMatchEnd, matchPos - lastMatchEnd); // Adiciona tudo que esta antes do template na string de resultado
    std::string templateKey = match[1].str();  // Retira o nome do template (o que esta entre as chaves)

    if (replacements.count(templateKey)) {
      result += replacements.at(templateKey); // se o templateKey existir no unordered_map, adicione a string substituida
    } else {
      result += match.str(); //se o templateKey não existir no unordered_map, adicione o template original
    }

    lastMatchEnd = matchPos + match.length(); // atualiza a posição do ultimo match
    it++;
  }

  result += html.substr(lastMatchEnd); // adicione o resto do html que sobrou da string original
  return result;
}

std::string readHTML(const std::string& filename, const std::unordered_map<std::string, std::string>& replacements) {
  std::ifstream file{std::string(filename + ".html"), std::ios::in | std::ios::binary};
  if (!file.is_open()) {
    std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
    return "";
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  return replaceTemplates(buffer.str(), replacements);
}

nlohmann::json Dailyhub::Login_On_Database(std::string user, std::string password) {
}

nlohmann::json Dailyhub::Send_Email(const User_Register_Email& user) {
  const auto authBearer = [](const std::string token) {
    return std::string("Bearer: " + token);
  };

  try {
    httplib::Client cli{"https://api.resend.com"};
    httplib::Headers headers = {
      {"Authorization", authBearer(std::getenv("SECRET_KEY_EMAIL"))},
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
    body_json["html"] = readHTML("../../mail/index", replacements);

    auto res = cli.Post("/emails", headers, body_json.dump(), "application/json");
    if (res->status == 200) {
      spdlog::info("Email enviado com sucesso para {}", user.email);
    }
    spdlog::error("Error ao enviar email: {}", user.email);
  } catch(std::exception& e) {
    spdlog::error("Erro ao Enviar email: {}", e.what());
  }
}

nlohmann::json Dailyhub::Register_On_Database(std::string username, std::string password, std::string email) {
  try {
    const auto [hash, salt]{PasswordHasher::to_hash_pass(password)};
    std::stringstream ss{};
    ss << "INSERT INTO users (hash, salt, username, email) VALUES ('" << hash << "', '" << salt << "', '" << username << "', '"  << email << "');";
    
    const auto response{DataBase::executeQuery(ss.str())};
    if (response.status) {
      spdlog::info("Usuário cadastrado com sucesso.");
      DataBase::cleanResult(response.result);
      User_Register_Email user;
      const std::string user_code = Utility::gerateString();
      user.name = username;
      user.code = user_code;
      user.message = "";
      user.email = email;
      Send_Email(user);
      Utility::useTokenUser({{email, user_code}});
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

bool Verify_Code_From_Email(const std::string& code) {
  try {
    if (Utility::getTokerrUser() == code) {
      return true;
    }

    return false;
  } catch (const std::exception& e) {
    spdlog::error("Error verificando código: {}", e.what());
    return false;
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
