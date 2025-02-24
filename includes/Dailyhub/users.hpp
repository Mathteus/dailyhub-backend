#ifndef DAILYHUB_USERS_HPP
#define DAILYHUB_USERS_HPP

#include "Dailyhub/schemas.hpp"

using namespace Dailyhub::Schemas::Users;

namespace Dailyhub {
namespace Users {
    Response_Register CreateUser(std::string username, std::string tag, std::string email, std::string hash);
    Response_UserLogin VerifyUser(std::string& hash, std::string email="", std::string username="");
    Response_GetPassword GetUserInfo(std::string userid);
    Response_Update UpdateUser(std::string hash="", std::string username="", std::string email="");
    Response_Delete DeleteUser(std::string userid);
};
};

#endif
