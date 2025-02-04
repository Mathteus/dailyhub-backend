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
find_package(jwt-cpp REQUIRED)

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
file(GLOB DAILYHUB_SOURCES "src/dailyhub/*.cpp")
file(GLOB DAILYHUB_HEADERS "src/dailyhub/*.hpp")
file(GLOB CORE_SOURCES "src/core/*.cpp")
file(GLOB CORE_HEADERS "src/core/*.hpp")

list(APPEND SRC ${DAILYHUB_SOURCES})
list(APPEND SRC ${DAILYHUB_HEADERS})
list(APPEND SRC ${CORE_SOURCES})
list(APPEND SRC ${CORE_HEADERS})

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
  jwt-cpp::jwt-cpp
  ${CURL_LIBRARIES}
  ${PostgreSQL_LIBRARIES}
  ${SODIUM_LIBRARIES}
)
