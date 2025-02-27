#include "Dailyhub/Core/auth.hpp"
#include "Dailyhub/Core/dotenv.hpp"


using Response = Dailyhub::Core::Errors::ResponseString;

std::string JwtSecret() {
	return Dailyhub::Core::DotEnv::get("JWT_SECRET", "TEST");
}

std::string Dailyhub::Core::AuthManager::generateJWT(const std::string& username) {
	auto token = jwt::create()
		.set_issuer("auth0")
		.set_type("JWS")
		.set_subject(username)
		.set_payload_claim("username", jwt::claim(username))
		.set_issued_at(std::chrono::system_clock::now())
		.set_expires_at(std::chrono::system_clock::now() + std::chrono::hours{1})
		.sign(jwt::algorithm::hs256{JwtSecret()});
	return token;
}

Response Dailyhub::Core::AuthManager::verifyJWT(const std::string& token) {
	Response res;
	res.success = false;
	res.data = std::nullopt;
	res.error = std::nullopt;
	try {
		auto decoded_token = jwt::decode(token);
		auto verifier = jwt::verify()
			.with_issuer("auth0")
			.allow_algorithm(jwt::algorithm::hs256{JwtSecret()});
		verifier.verify(decoded_token);

		const auto& payload_json = decoded_token.get_payload();
		auto payload = nlohmann::json::parse(payload_json);
		if (payload.contains("username")) {
			res.data = payload["username"].get<std::string>();
			res.success = true;
			res.error = std::nullopt;
		} else {
			std::stringstream ss;
			ss << "Token válido, mas username não encontrado no payload para o token: " << token;
			spdlog::error(ss.str());
			res.error = ss.str();
			res.success = false;
			res.data = std::nullopt;
		}
	} catch (const std::exception& e) {
		const std::string error{e.what()};
		spdlog::error("{}", error);
		res.error = error;
		res.success = false;
		res.data = std::nullopt;
	}

	return res;
}
