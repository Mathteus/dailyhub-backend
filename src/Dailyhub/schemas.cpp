#include "Dailyhub/schemas.hpp"

Dailyhub::Schemas::Users::DTO_User Dailyhub::Schemas::Users::perseUser(const nlohmann::json& j) {
    using User = Dailyhub::Schemas::Users::DTO_User;
    User p;
    p.user_id = j.at("user_id").get<std::string>();
    p.hash = j.at("hash").get<std::string>();
    p.name = j.at("name").get<std::string>();
    p.tag = j.at("tag").get<std::string>();
    p.email = j.at("email").get<std::string>();

    // Para last_login e created_at
    std::string last_login_str = j.at("last_login").get<std::string>();
    p.last_login = Dailyhub::Core::Utility::parse_date_time(last_login_str);

    std::string created_at_str = j.at("created_at").get<std::string>();
    p.created_at = Dailyhub::Core::Utility::parse_date_time(created_at_str);
    return p;
}

Dailyhub::Schemas::Users::DTO_User_Login Dailyhub::Schemas::Users::Parse_DTO_Login(const nlohmann::json& j) {
    using User = Dailyhub::Schemas::Users::DTO_User_Login;
    User p;
    p.user_id = j.at("user_id").get<std::string>();
    p.email = j.at("email").get<std::string>();
    p.name = j.at("name").get<std::string>();
    p.tag = j.at("tag").get<std::string>();
    return p;
}
