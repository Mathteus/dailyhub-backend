#include "Dailyhub/Core/dotenv.hpp"

void load(const char* path=".env") {
  dotenv::env.load_dotenv(path);
}

std::string Dailyhub::Core::Dotenv::get(const std::string& key, const char* placeholder) {
  std::string env{dotenv::env[key]};
  if (env.size()) {
    return env;
  }
  return placeholder;
}
