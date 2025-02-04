#ifndef AUTH_HPP
#define AUTH_HPP

#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include <thread>
#include <map>
#include <mutex>
#include <jwt-cpp/jwt.h>
#include <random>
#include <sstream>

class AuthManager : public std::enable_shared_from_this<AuthManager> {
public:
  static std::string generateJWT(const std::string& username);
  static bool verifyJWT(const std::string& token);
  
  AuthManager() = default;
  ~AuthManager() = default;

private:
  static const std::string jwtSecret;
  static std::string generateRandomCode(int length = 6);
};

#endif
