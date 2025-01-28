#ifndef KANABAN_HPP
#define KANABAN_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <map>
#include "../core/database.hpp"
#include "../core/utility.hpp"

class Kanban {
private:
  typedef struct {
    std::string taskid;
    std::string userid;
    std::string title;
    uint16_t status;
    std::string description;
    std::time_t createat;
    std::time_t lastupdate;
  } Items;

public:
  Kanban() = default;
  ~Kanban() = default;

  void createTask(const std::string& userid, const std::string& title, uint16_t status, const std::string& description);
  void updateTask(const std::string& userid, const std::string& taskid, std::map<std::string, std::string> updates);
  void deleteTask(const std::string& userid, const std::string& taskid);
  void listTasksByStatus(const std::string& userid, uint16_t status);
  void listAllTasks(const std::string& userid);
};

#endif