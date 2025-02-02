#include "kanban.hpp"

void Kanban::createTask(const std::string& userid, const std::string& title, uint16_t status, const std::string& description) {
  std::stringstream query;
  // query << "insert into kanban (userid, taskid, title, description, status) values (" << userid << "," << taskid << "," << title << "," << description << "," << status << ");";
  DataBase::executeQuery(query.str());
}

void updateTask(const std::string& userid, const std::string& taskid, std::map<std::string, std::string> updates) {
  std::vector<std::string> fields = {"", "", ""};
  std::stringstream query;
  query << "update kanban ";
  
  if (updates.count("title")) {
    fields[0] = updates["title"];
    query << " set title = '" << fields[0] << "'";
  }

  if (updates.count("description")) {
    fields[1] = updates["description"];
    query << " set description = '" << fields[1] << "';";
  }

  if (updates.count("status")) {
    fields[2] = updates["status"];
    query << " set status = " << Utility::Integer(fields[2]);
  }
  
  DataBase::executeQuery(query.str());
}

void Kanban::deleteTask(const std::string& userid, const std::string& taskid) {
  std::stringstream query;
  query << "delete from kanban where userid = " << userid << " and taskid = " << taskid << "';";
  DataBase::executeQuery(query.str());
}

void Kanban::listTasksByStatus(const std::string& userid, uint16_t status) {
  std::stringstream query;
  query << "select * from kanban where userid = " << userid << " and status = " << status << ';';
  DataBase::executeQuery(query.str());
}

void Kanban::listAllTasks(const std::string& userid) {
  std::stringstream query;
  query << "select * from kanban where userid = " << userid << ';';
  DataBase::executeQuery(query.str());
}