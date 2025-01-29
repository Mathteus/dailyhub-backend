#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "../core/database.hpp"
#include "../core/server.hpp"
#include "../core/utility.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <httplib.h>

class DailyHub {
public: 
  DailyHub();
  ~DailyHub();
  void run();
};

#endif