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
#include "date/date.h"

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
  std::string gerateString(const uint8_t lenght);
  const char* gerateStringC(const uint8_t lenght);
  std::string gerateCode(int seed);
  time_t Date();
  std::string base64_encode(const std::string& input);
  std::string base64_decode(const std::string& input);
  std::string readFilesSQL(const std::string& sqlFile);
  bool IsValidEmail(const std::string& email);
  bool ContainsSymbols(const std::string& str);
  std::string bytes_to_hex_string(const std::vector<unsigned char>& bytes);
  std::string time_point_to_string(const std::chrono::system_clock::time_point& tp);
  std::chrono::system_clock::time_point parse_date_time(const std::string& time_str);
  std::string replaceTemplates(std::string html, const std::unordered_map<std::string, std::string>& replacements);
  std::string readFile(const std::string& filename, const std::unordered_map<std::string, std::string>& replacements);
};
};
};

#endif
