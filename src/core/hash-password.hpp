#ifndef PASSWORD_HASHER_HPP
#define PASSWORD_HASHER_HPP

#include <string>
#include <tuple>
#include <stdexcept>
#include <sstream>
#include <iomanip>

namespace PasswordHasher {
  // Gera o hash da senha e retorna o hash e o salt como um std::tuple
  std::tuple<std::string, std::string> to_hash_pass(const std::string& password);

  // Verifica se a senha fornecida corresponde ao hash armazenado
  bool verify_password(const std::string& password, const std::string& stored_hash, const std::string& stored_salt);
};

#endif