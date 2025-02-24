#include "Dailyhub/Core/dotenv.hpp"

void Dailyhub::Core::DotEnv::load(const char* path=".env") {
    dotenv::init(path);
}

std::string Dailyhub::Core::DotEnv::get(const std::string& key, const char* placeholder) {
    std::string env{dotenv::getenv(key.c_str(), placeholder)};
    if (env.size()) {
        return env;
    }
    return placeholder;
}
