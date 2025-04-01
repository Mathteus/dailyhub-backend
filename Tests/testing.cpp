#include "Dailyhub/Core/dotenv.hpp"
#include "Dailyhub/Core/database.hpp"
#include "Dailyhub/Core/httplib.h"
#include "Dailyhub/schemas.hpp"
#include "Dailyhub/Core/server.hpp"
#include "Dailyhub/routes.hpp"

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>

#include "restclient-cpp/connection.h"
#include "restclient-cpp/restclient.h"

const std::string PATH_ENV_TEST{"/media/henrique/A/dailyhub-backend/Tests/test.env"};

std::string verifyEnvText(std::string key) {
  return Dailyhub::Core::DotEnv::get(key, "ERROR");
}

bool Test_execQuery() {
  const char* const ptrArray[] = {"LOCAL"};
  Dailyhub::Core::DataBase::ParamsQuery params_no_params = {0, ptrArray};
  const auto response = Dailyhub::Core::DataBase::execQuery("SELECT now();", params_no_params);
  return response.success;
}

nlohmann::json Test_Select() {
  const char* const ptrArray[] = {"LOCAL"};
  Dailyhub::Core::DataBase::ParamsQuery params_no_params = {1, ptrArray};
  const auto response = Dailyhub::Core::DataBase::Select("SELECT * FROM env WHERE current_locale = $1;", params_no_params);
  return response.data;
}

bool create_profile() {
  try {
    Dailyhub::Schemas::Users::DTO_USER_REGISTER user;
    user.code = "751257";
    user.email = "mathteus35@gmail.com";
    user.message = "Registrar Usuário";
    user.name = "Matheus Henrique";
    user.password = "senhas_test";
    user.tag = "Mathteus";

    RestClient::init();
    const std::unique_ptr<RestClient::Connection> conection{std::make_unique<RestClient::Connection>("http://localhost:4512")};

    RestClient::HeaderFields headers;
    headers["Content-Type"] = "application/json";
    headers["x-api-key"] = Dailyhub::Core::DotEnv::get("X_API_KEY", "");
    conection->SetHeaders(headers);

    const nlohmann::json json_body{Dailyhub::Schemas::Users::DTO_User_Register_To_JSON(user)};
    const RestClient::Response response{conection->post("/api/v1/register", json_body.dump())};
    RestClient::disable();

    if (response.code == 201) {
      std::cout << response.body << '\n';
      return true;
    }
  } catch (std::exception& e) {
    std::cerr << e.what() << '\n';
    RestClient::disable();
  }

  return false;
}

bool login_profile() {
  try {
    nlohmann::json user_login{
      {"username", "Mathteus"},
      {"password", "senhas_test"}
    };

    RestClient::init();
    const std::unique_ptr<RestClient::Connection> conection{std::make_unique<RestClient::Connection>("http://localhost:4512")};

    RestClient::HeaderFields headers;
    headers["Content-Type"] = "application/json";
    headers["x-api-key"] = Dailyhub::Core::DotEnv::get("X_API_KEY", "");
    conection->SetHeaders(headers);

    const nlohmann::json json_body{Dailyhub::Schemas::Users::DTO_User_Register_To_JSON(user)};
    const RestClient::Response response{conection->post("/api/v1/register", json_body.dump())};
    RestClient::disable();

    if (response.code == 201) {
      std::cout << response.body << '\n';
      return true;
    }
  } catch (std::exception& e) {
    std::cerr << e.what() << '\n';
    RestClient::disable();
  }

  return false;
}

bool verify_api_online() {
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(200ms);

  try {
    RestClient::init();
    const std::unique_ptr<RestClient::Connection> conection{std::make_unique<RestClient::Connection>("http://localhost:4512")};
    const RestClient::Response response{conection->get("/isonline")};
    RestClient::disable();

    if (response.code == 200) {
      return true;
    }
  } catch (std::exception& e) {
    std::cerr << e.what() << '\n';
    RestClient::disable();
  }

  return false;
}

TEST(TESTS_ENV, VERIFY_TEXT) {
  ASSERT_EQ("TESTING", verifyEnvText("TEXT"));
}

TEST(TEST_DATABASE, CONNECTION) {
  ASSERT_TRUE(Dailyhub::Core::DataBase::connect());
}

TEST(TEST_DATABASE, ISCONNECTED) {
  ASSERT_TRUE(Dailyhub::Core::DataBase::isConnected());
}

TEST(TEST_DATABASE, VERIFY_EXEC_QUERY) {
  ASSERT_TRUE(Test_execQuery());
}

TEST(TEST_DATABASE, VERIFY_SELECT_QUERY) {
  const nlohmann::json dataJson{Test_Select()};
  const nlohmann::json res{dataJson[0][0][0]};
  ASSERT_EQ("LOCAL", res[0]["current_locale"]);
}

TEST(TEST_SERVER, START) {
  std::function<void(crow::SimpleApp& app)> func{Dailyhub::Routes::Configure};
  ASSERT_TRUE(Dailyhub::Core::Servidor::Start(func));
}

TEST(TEST_SERVER, VERIFY_ONLINE) {
  ASSERT_TRUE(verify_api_online());
}

TEST(TEST_SERVER, CREATE_NEW_USER) {
  ASSERT_TRUE(create_profile());
}

TEST(TEST_SERVER, CLOSE) {
  ASSERT_TRUE(Dailyhub::Core::Servidor::Stop());
}

TEST(TEST_DATABASE_END, CLOSE_CONNECTION) {
  ASSERT_TRUE(Dailyhub::Core::DataBase::close());
}

TEST(TEST_DATABASE_END, ALREADY_CLOSE) {
  ASSERT_FALSE(Dailyhub::Core::DataBase::isConnected());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  Dailyhub::Core::DotEnv::load(PATH_ENV_TEST.c_str());
  return RUN_ALL_TESTS();
}
