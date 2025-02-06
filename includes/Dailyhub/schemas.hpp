#ifndef SCHEMAS_HPP
#define SCHEMAS_HPP

#include <cstdlib>
#include <string>
#include <nlohmann/json.hpp>

// CREATE TABLE IF NOT EXISTS users (
//   user_id VARCHAR(6) NOT NULL DEFAULT nanoid(6),
//   hash VARCHAR(30) NOT NULL,
//   salt VARCHAR(30) NOT NULL,
//   role VARCHAR(10) NOT NULL DEFAULT 'user',
//   name VARCHAR(30) NOT NULL,
//   tag VARCHAR(26) NOT NULL UNIQUE,
//   email VARCHAR(60) NOT NULL UNIQUE,
//   last_login DATE NOT NULL DEFAULT now(),
//   created_at DATE NOT NULL DEFAULT now(),
//   CONSTRAINT pk_userid PRIMARY KEY (user_id)
// );

namespace Dailyhub {
namespace Schemas {


typedef struct {
    char[6] user_id;
    char[30] hash;
    char[30] salt

} users;

typedef struct {
  bool status;
  std::string error;
} ResponseDatabase;

};
};

#endif // SCHEMAS_HPP
