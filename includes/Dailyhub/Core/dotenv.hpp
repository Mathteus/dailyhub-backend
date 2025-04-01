#ifndef DAILYHUB_DOTENV_HPP
#define DAILYHUB_DOTENV_HPP

#include <laserpants/dotenv-0.9.3/dotenv.h>
#include <string>

namespace Dailyhub {
namespace Core {
namespace DotEnv {
  std::string get(const std::string& key, const char* placeholder);
  void load(const char* path);
};
};
};

#endif
