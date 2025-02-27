#include "Dailyhub/Core/hash-password.hpp"
#include <bcrypt/BCrypt.hpp>

using Response = Dailyhub::Core::Errors::ResponseString;

Response Dailyhub::Core::PasswordHasher::to_hash_pass(const std::string& password) {
	Response res;
	char salt[BCRYPT_HASHSIZE];
	if (bcrypt_gensalt(12, salt) != 0) {
		res.success = false;
		res.error = "Erro ao gerar o salt Bcrypt.";
		res.data = std::nullopt;
		return res;
	}

	char hash[BCRYPT_HASHSIZE];
	if (bcrypt_hashpw(password.c_str(), salt, hash) != 0) {
		res.success = false;
		res.error = "Erro ao gerar o hash Bcrypt.";
		res.data = std::nullopt;
		return res;
	}

	res.success = true;
	res.data = hash;
	res.error = std::nullopt;
	return res;
}

bool Dailyhub::Core::PasswordHasher::verify_password(const std::string& password, const std::string& stored_hash) {
	return static_cast<bool>(BCrypt::validatePassword(password, stored_hash));
}
