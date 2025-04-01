#ifndef DAILYHUB_PASSWORD_HASHER_HPP
#define DAILYHUB_PASSWORD_HASHER_HPP

#include <string>
#include <map>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include "Dailyhub/Core/error_handler.hpp"

namespace Dailyhub {
namespace Core {
namespace PasswordHasher {
  Dailyhub::Core::Errors::ResponseString to_hash_pass(const std::string& password);
  bool verify_password(const std::string& password, const std::string& stored_salt);
};
};
};

#endif
