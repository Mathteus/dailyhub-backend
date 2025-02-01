cmake_minimum_required(VERSION 3.15)
project(Dailyhub_Server)

# Dependencies
find_package(Crow REQUIRED)
find_package(Threads REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(spdlog REQUIRED)
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(OpenSSL REQUIRED)

# C++ Settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_STATIC "${CMAKE_CXX_FLAGS_STATIC} -static")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

# LIBS Settings
set(POSTGRESQL_INCLUDE_DIR "/usr/include/postgresql")
set(SODIUM_SOURCE "/usr/include")
set(SODIUM_LIBRARIES "/usr/lib/x86_64-linux-gnu/libsodium.a")
include_directories(${POSTGRESQL_INCLUDE_DIR})
include_directories(${DOTENV_SOURCE})
include_directories(${SODIUM_SOURCE})

# SOURCE
set(SRC
  src/main.cpp
  src/core/server.hpp
  src/core/server.cpp
  src/core/utility.hpp
  src/core/utility.cpp
  src/core/database.hpp
  src/core/database.cpp
  src/core/hash-password.cpp
  src/core/hash-password.hpp
  src/core/httplib.h
  src/dailyhub/application.hpp
  src/dailyhub/application.cpp
  src/dailyhub/kanban.hpp
  src/dailyhub/kanban.cpp
)

# EXE and LIBRARIES C++
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC
  Crow::Crow
  Threads::Threads
  spdlog::spdlog
  nlohmann_json::nlohmann_json
  OpenSSL::SSL
  OpenSSL::Crypto
  ${CURL_LIBRARIES}
  ${PostgreSQL_LIBRARIES}
  ${SODIUM_LIBRARIES}
)
