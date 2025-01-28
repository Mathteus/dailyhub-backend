#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "../core/database.hpp"
#include "../core/rest_client.hpp"
#include "../core/server.hpp"
#include "../core/utility.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

class DailyHub {
public: 
  DailyHub();
  ~DailyHub();
  void run();
};

#endif