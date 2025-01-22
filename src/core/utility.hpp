#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <random>
#include <ctime>

namespace Utility {
  uint32_t Integer(std::string str);
  std::string String(uint32_t num);
  int random(int min, int max);
  int random(int max);
  std::string gerateString();
  std::string gerateCode(int seed);
  time_t Date();
  std::string base64_encode(const std::string& input);
  std::string base64_decode(const std::string& input);
}

#endif