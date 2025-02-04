#include "auth.hpp"

static const std::string jwtSecret{""};

std::string AuthManager::generateJWT(const std::string& username) {
  auto token = jwt::create()
    .set_issuer("meu_servidor")
    .set_type("JWS")
    .set_payload_claim("username", jwt::claim(username))
    .set_issued_at(std::chrono::system_clock::now())
    .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours(1))
    .sign(jwt::algorithm::hs256{jwtSecret});
  return token;
}

bool AuthManager::verifyJWT(const std::string& token) {
  try {
    jwt::decode(token, jwt::algorithm::hs256{jwtSecret},
    jwt::validation::leeway(std::chrono::seconds{10}));
    return true;
  } catch (const std::exception&) {
    return false;
  }
}

std::string AuthManager::generateRandomCode(int length) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, 9);
  std::stringstream ss;
  for (int i = 0; i < length; ++i) {
    ss << distrib(gen);
  }
  return ss.str();
}
