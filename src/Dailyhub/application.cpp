#include "Dailyhub/application.hpp"

using namespace Dailyhub::Core;

// nlohmann::json Dailyhub::Application::Login(std::string user, std::string password) {

// }

void Dailyhub::Application::Send_Email(const Dailyhub::Schemas::Users::User_Register_Email& user) {
	const auto authBearer = []() {
		return std::string("Bearer: " + DotEnv::get("SECRET_KEY_EMAIL", ""));
	};

	try {
		httplib::Client cli{"https://api.resend.com"};
		httplib::Headers headers = {
			{"Authorization", authBearer()},
			{"Content-Type", "application/json"}
		};

		const std::unordered_map<std::string, std::string> replacements{{
			{"USERNAME", user.name},
			{"CODE", user.code},
			{"MESSAGE_TEXT", user.message}
		}};

		nlohmann::json body_json;
		body_json["from"] = "Acme <onboarding@resend.dev>";
		body_json["to"] = nlohmann::json::array({ user.email });
		body_json["subject"] = "Registro na Dailyhub";
		body_json["html"] = Dailyhub::Core::Utility::readHTML("../../mail/index", replacements);

		auto res = cli.Post("/emails", headers, body_json.dump(), "application/json");
		if (res->status == 200) {
			spdlog::info("Email enviado com sucesso para {}\n", user.email);
		}
		spdlog::error("Error ao enviar email: {}\n", user.email);
	} catch(std::exception& e) {
		spdlog::error("Erro ao Enviar email: {}\n", e.what());
	}
}

nlohmann::json Dailyhub::Application::Register(nlohmann::json user_json) {
	using User_Register = Dailyhub::Schemas::Users::DTO_USER_REGISTER;
	const User_Register user = Dailyhub::Schemas::Users::Parse_DTO_User_Register(user_json);
	nlohmann::json res_json;

	const auto email = [user]() {
		User_Register_Email user_email;
		user.name = user.username;
		user.code = user.code;
		user.message = "Registro Dailyhub";
		user.email = user.email;
		Dailyhub::Application::Send_Email(user);
	};

	try {
		const auto hash{PasswordHasher::to_hash_pass(user.password)};
		if (!hash.success && !hash.data) {
			return {
				{"status", 400},
				{"message", hash.error->data()}
			};
		}

		auto response{Dailyhub::Users::CreateUser(user.username, user.tag, user.email, hash.data->data())};
		if (response.success) {
			spdlog::info("Usuário cadastrado com sucesso.\n");
			email();
			return {
				{"status", 201},
				{"message", ""}
			};
		}

		spdlog::error("Erro ao cadastrar usuário: {}\n", response.error->data());
		res_json = {
			{"status", 400},
			{"message", response.error->data()}
		};
	} catch (const std::exception& e) {
		spdlog::error("Error hashing password: {}\n", e.what());
		res_json = {
			{"status", 500},
			{"message", e.what()}
		};
	}

	return res_json;
}

Dailyhub::Application::Application() {
	Dailyhub::Core::DotEnv::load(".env");
	if (Dailyhub::Core::DataBase::connect()) {
		Dailyhub::Core::Servidor::Start(Dailyhub::Routes::Configure);
		spdlog::info("Application is running!");
	}
}

Dailyhub::Application::~Application() {
	Dailyhub::Core::Servidor::Stop();
	Dailyhub::Core::DataBase::close();
	spdlog::info("Application closing!");
}
