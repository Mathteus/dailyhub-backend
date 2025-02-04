#include "hash-password.hpp"
#include <sodium.h>

#define SALT_SIZE crypto_pwhash_SALTBYTES
#define HASH_SIZE crypto_pwhash_BYTES_MAX

std::tuple<std::string, std::string> PasswordHasher::to_hash_pass(const std::string& password) {
  if (sodium_init() == -1) {
    return {"", ""};
  }

  unsigned char salt[SALT_SIZE];
  unsigned char hash[HASH_SIZE];
  randombytes_buf(salt, SALT_SIZE);

  if (crypto_pwhash(hash, HASH_SIZE, password.c_str(), password.length(), salt, crypto_pwhash_OPSLIMIT_SENSITIVE, crypto_pwhash_MEMLIMIT_SENSITIVE, crypto_pwhash_ALG_DEFAULT) != 0)
  {
    return {"", ""};
  }

  std::stringstream ss_salt;
  for (int i = 0; i < SALT_SIZE; ++i) {
    ss_salt << std::hex << std::setw(2) << std::setfill('0') << (int)salt[i];
  }

  std::stringstream ss_hash;
  for (int i = 0; i < HASH_SIZE; ++i) {
    ss_hash << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
  }

  return {std::string(ss_hash.str()), std::string(ss_salt.str())};
}

bool PasswordHasher::verify_password(const std::string& password, const std::string& stored_hash, const std::string& stored_salt) {
  if (sodium_init() == -1) {
    return false;
  }

  unsigned char salt[SALT_SIZE];
  unsigned char hash[HASH_SIZE];
   
  if (stored_salt.length() != SALT_SIZE*2) {
    return false;
  }

  if (stored_hash.length() != HASH_SIZE*2) {
    return false;
  }

  for (size_t i = 0; i < stored_salt.length(); i += 2) {
    std::string byteString = stored_salt.substr(i, 2);
    salt[i/2] = (unsigned char)std::stoi(byteString, nullptr, 16);
  }

  if (crypto_pwhash(hash, HASH_SIZE, password.c_str(), password.length(), salt, crypto_pwhash_OPSLIMIT_SENSITIVE, crypto_pwhash_MEMLIMIT_SENSITIVE, crypto_pwhash_ALG_DEFAULT) != 0) {
    return false;
  }

  std::stringstream ss_hash;
  for (int i = 0; i < HASH_SIZE; ++i) {
    ss_hash << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
  }
   
  return ss_hash.str() == stored_hash;
}
