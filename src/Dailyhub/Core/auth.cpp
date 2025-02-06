#include "Dailyhub/Core/auth.hpp"

static const std::string jwtSecret{std::getenv("JWT_SECRET")};

std::string AuthManager::generateJWT(const std::string& username) {
  auto token = jwt::create()
    .set_issuer("auth0")
    .set_type("JWS")
    .set_subject(username)
    .set_payload_claim("username", jwt::claim(username))
    .set_issued_at(std::chrono::system_clock::now())
    .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours{1})
    .sign(jwt::algorithm::hs256{jwtSecret});
  return token;
}

Auth_Response AuthManager::verifyJWT(const std::string& token) {
  Auth_Response res;
  res.success = false;
  res.username = "";
  try {
    auto decoded_token = jwt::decode(token);
    auto verifier = jwt::verify()
      .with_issuer("auth0")
      .allow_algorithm(jwt::algorithm::hs256{jwtSecret});
    verifier.verify(decoded_token);
    const auto& payload_json = decoded_token.get_payload();
    auto payload = nlohmann::json::parse(payload_json);
    if (payload.contains("username")) {
      res.username = payload["username"].get<std::string>();
      res.success = true;
      return res;
    } else {
      std::stringstream ss;
      ss << "Token válido, mas username não encontrado no payload para o token: " << token;
      spdlog::error(ss.str());
      return res;
    }
  } catch (const std::exception& e) {
    spdlog::error("{}", e.what());
    return res;
  }
}
