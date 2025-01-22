cmake_minimum_required(VERSION 3.15)
project(DailyHub_Server)

find_package(Crow REQUIRED)
find_package(Threads REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(spdlog REQUIRED)
find_package(CURL REQUIRED)

set(CMAKE_C_FLAGS_STATIC "${CMAKE_C_FLAGS_STATIC} -static")
set(CMAKE_CXX_FLAGS_STATIC "${CMAKE_CXX_FLAGS_STATIC} -static")

set(POSTGRESQL_INCLUDE_DIR "/usr/include/postgresql")
include_directories(${POSTGRESQL_INCLUDE_DIR})
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
)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME}
  PUBLIC
  Crow::Crow
  Threads::Threads
  spdlog::spdlog
  ${CURL_LIBRARIES}
  ${PostgreSQL_LIBRARIES}
)
