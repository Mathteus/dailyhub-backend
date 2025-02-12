#ifndef DAILYHUB_UTILITY_HPP
#define DAILYHUB_UTILITY_HPP

#include <random>
#include <ctime>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <chrono>
#include <thread>
#include <vector>
#include <map>
#include <mutex>
#include <algorithm>
#include <spdlog/spdlog.h>
#include <regex>

namespace Dailyhub {
namespace Core {
struct TimedData {
  std::shared_ptr<std::map<std::string, std::string>> data;
  int seconds;
};

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
  std::string readFilesSQL(const std::string& sqlFile);
  bool IsValidEmail(const std::string& email);
  bool ContainsSymbols(const std::string& str);
};
};
};

#endif
