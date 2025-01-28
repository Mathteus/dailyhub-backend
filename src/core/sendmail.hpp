#ifndef SENDMAIL_HPP
#define SENDMAIL_HPP

#include <string>

struct EmailData {
  std::string fromAddress;
  std::string fromName;
  std::string toAddress;
  std::string toName;
  std::string subject;
  std::string body;
};

namespace Mail {
  std::string generateVerificationCode(int length);
  bool sendEmail(const EmailData& email, const std::string& smtp_server, const std::string& smtp_user, const std::string& smtp_password, const std::string& htmlTemplatePath);
  void Setup();
}

#endif