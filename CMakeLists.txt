cmake_minimum_required(VERSION 3.15)
project(DailyHub_Server)

find_package(Crow REQUIRED)
find_package(Threads REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(spdlog REQUIRED)
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

set(CMAKE_C_FLAGS_STATIC "${CMAKE_C_FLAGS_STATIC} -static")
set(CMAKE_CXX_FLAGS_STATIC "${CMAKE_CXX_FLAGS_STATIC} -static")

set(POSTGRESQL_INCLUDE_DIR "/usr/include/postgresql")
set(DOTENV_SOURCE "/usr/local/include/laserpants/dotenv-0.9.3")
include_directories(${POSTGRESQL_INCLUDE_DIR})
include_directories(${DOTENV_SOURCE})
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

set(SRC
  src/main.cpp
  src/core/server.hpp
  src/core/server.cpp
  src/core/utility.hpp
  src/core/utility.cpp
  src/core/database.hpp
  src/core/database.cpp
  src/core/rest_client.hpp
  src/core/rest_client.cpp
  src/dailyhub/application.hpp
  src/dailyhub/application.cpp
  src/dailyhub/kanban.hpp
  src/dailyhub/kanban.cpp
)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC
  Crow::Crow
  Threads::Threads
  spdlog::spdlog
  nlohmann_json::nlohmann_json
  ${CURL_LIBRARIES}
  ${PostgreSQL_LIBRARIES}
)
