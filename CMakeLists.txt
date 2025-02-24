cmake_minimum_required(VERSION 3.15)
project(Dailyhub_Server VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Backend Dailyhub")

# Dependencies
find_package(Crow REQUIRED)
find_package(Threads REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(spdlog REQUIRED)
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(jwt-cpp REQUIRED)
find_package(GTest REQUIRED)
find_package(date REQUIRED)

# C++ Settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_STATIC "${CMAKE_CXX_FLAGS_STATIC} -static -static-libgcc -static-libstdc++")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options(-Wall -Wextra -Wpedantic)
	add_compile_options(-fno-omit-frame-pointer)
endif()

if(${CMAKE_BUILD_TYPE} MATCHES Debug)
	set(CMAKE_CXX_FLAGS "-fsanitize=address -fsanitize=undefined -fsanitize=bounds -fsanitize=leak -g")
	set(CMAKE_C_FLAGS "-fsanitize=address -fsanitize=undefined -fsanitize=bounds -fsanitize=leak -g")
	set(CMAKE_EXE_LINKER_FLAGS "-fsanitize=address -fsanitize=undefined -fsanitize=bounds -fsanitize=leak")
	set(CMAKE_MODULE_LINKER_FLAGS "-fsanitize=address -fsanitize=undefined -fsanitize=bounds -fsanitize=leak")
	# set(CMAKE_CXX_FLAGS "-fsanitize=thread -fsanitize=bounds -g")
	# set(CMAKE_C_FLAGS "-fsanitize=thread -fsanitize=bounds  -g")
	# set(CMAKE_EXE_LINKER_FLAGS "-fsanitize=thread -fsanitize=bounds")
	# set(CMAKE_MODULE_LINKER_FLAGS "-fsanitize=thread -fsanitize=bounds")
endif(${CMAKE_BUILD_TYPE} MATCHES Debug)

# LIBS Settings
set(DOTENV_INCLUDE "/usr/local/include/cpp-dotenv/")
set(POSTGRESQL_INCLUDE_DIR "/usr/include/postgresql/")
set(BCRYPT_SOURCE "/usr/include/bcrypt/")
set(BCRYPT_LIBRARIES -lbcrypt)
set(DOTENV_HEADER "/usr/local/include/laserpants/dotenv-0.9.3/")
include_directories(${POSTGRESQL_INCLUDE_DIR})
include_directories(${BCRYPT_SOURCE})
include_directories(${DOTENV_INCLUDE})
include_directories(${DOTENV_HEADER})

# SOURCE
set(SOURCE_DIR ${CMAKE_SOURCE_DIR})
set(INCLUDE_DIR ${SOURCE_DIR}/includes)
set(SRC_DIR ${SOURCE_DIR}/src)
set(TEST_DIR ${SOURCE_DIR}/Tests)

file(GLOB_RECURSE HEADERS "${INCLUDE_DIR}/*.hpp")
file(GLOB_RECURSE SOURCE "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE TESTS "${TEST_DIR}/*.hpp" "${TEST_DIR}/*.cpp")
include_directories(${INCLUDE_DIR})

list(APPEND SRC ${HEADERS})
list(APPEND SRC ${SOURCE})
list(APPEND SRC ${TESTS})

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
  date::date
  ${CURL_LIBRARIES}
  ${PostgreSQL_LIBRARIES}
	${BCRYPT_LIBRARIES}
)
