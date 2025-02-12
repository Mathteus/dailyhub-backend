#ifndef DAILYHUB_DOTENV_HPP
#define DAILYHUB_DOTENV_HPP

#include <dotenv.h>
#include <string>

namespace Dailyhub {
namespace Core {

namespace Dotenv {
  std::string get(const std::string& key, const char* placeholder);
};
};
};

#endif
