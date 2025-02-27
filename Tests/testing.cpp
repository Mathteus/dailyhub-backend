#include "Dailyhub/Core/dotenv.hpp"
#include "Dailyhub/Core/database.hpp"
#include "Dailyhub/Core/httplib.h"
#include "Dailyhub/schemas.hpp"

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>

std::string verifyEnvText(std::string key) {
  return Dialyhub::Core::DotEnv::get(key, "ERROR");
}

bool getNanoId() {
  Dailyhub::Core::DataBase::ParamsQuery params;
  params.colums = 0;
  params.params = [];
  const auto response = Dialyhub::Core::DataBase::execQuery("select nanoid(5);", params);
  return response.success;
}

bool create_profile() {
	try {
    Dailyhub::Schemas::Users::DTO_USER_REGISTER user;
    user.code = "751257";
    user.email = "Mathteus35@gmail.com";
    user.messasge = "Registrar Usuário";
    user.name = "Matheus Henrique";
    user.password = "senhas_test";
    user.tag = "Mathteus";

		httplib::Client cli{Dialyhub::Core::DotEnv::get("URL_BASE", "http://localhost:7845")};
		httplib::Headers headers = {
			{"Authorization", Dialyhub::Core::DotEnv::get("X_API_KEY", "ERROR")},
			{"Content-Type", "application/json"}
		};

		nlohmann::json body_json{Dailyhub::Schemas::Users::DTO_User_Register_To_JSON(user)};
		auto res = cli.Post("/api/v1/register", headers, body_json.dump(), "application/json");
		if (res->status == 200) {
			return true;
		}
	} catch(std::exception& e) {
    return false;
	}

  return false;
}

TEST(TESTS_ENV, VERIFY_TEXT) {
  ASSERT_EQ("TESTING", verifyEnvText("TEXT"));
}

TEST(TEST_DATABASE, CONNECTION) {
  ASSERT_TRUE(Dailyhub::Core::DataBase::connect());
}

TEST(TEST_DATABASE, VERIFY_DATABASE_OPEN) {
  ASSERT_TRUE(getNanoId());
}

TEST(TEST_DATABASE, REGISTER_USER) {
  ASSERT_TRUE(create_profile());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  Dailyhub::Core::DotEnv::load("test.env");
  return RUN_ALL_TESTS();
}
