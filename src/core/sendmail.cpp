#include "sendmail.hpp"
#include <iostream>
#include <sstream>
#include <random>
#include <curl/curl.h>
#include <stdexcept>
#include <fstream>

std::string Mail::generateVerificationCode(int length) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, 9);
  std::string code;
  for (int i = 0; i < length; ++i) {
    code += std::to_string(distrib(gen));
  }
  return code;
}

// Função de callback para o libcurl
size_t discard_data(void *ptr, size_t size, size_t nmemb, void *userdata) {
  return size * nmemb;
}

// Função para carregar o template HTML
std::string loadHtmlTemplate(const std::string& templatePath) {
  std::ifstream file(templatePath);
  if (!file.is_open()) {
    throw std::runtime_error("Não foi possível abrir o arquivo de template: " + templatePath);
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}


// Função para substituir placeholders no template HTML
std::string replacePlaceholders(std::string html, const std::string& userName, const std::string& verificationCode, char state='R') {
  size_t pos;
  pos = html.find("USERNAME");
  if(pos != std::string::npos) {
    html.replace(pos, std::string("USERNAME").length(), userName);
  }

  pos = html.find("CODE");
  if (pos != std::string::npos) {
    html.replace(pos, std::string("CODE").length(), verificationCode);
  }

  pos = html.find("MESSAGE_TEXT");
  if (pos != std::string::npos) {
    std::string message{"Use este código para validar seu"};
    message += state == 'R' ? " cadastro." : " Login.";
    html.replace(pos, std::string("MESSAGE_TEXT").length(), message);
  }
  return html;
}

// Função para enviar o e-mail
bool Mail::sendEmail(const EmailData& email, const std::string& smtp_server, const std::string& smtp_user, const std::string& smtp_password, const std::string& htmlTemplatePath) {
  CURL *curl;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if(curl) {
    std::string recipients = "<" + email.toAddress + ">";
    struct curl_slist *headerlist = NULL;
    std::string customHeader = "From: \"" + email.fromName + "\" <" + email.fromAddress + ">";
    headerlist = curl_slist_append(headerlist, customHeader.c_str());
    headerlist = curl_slist_append(headerlist, "Content-Type: text/html");

    try {
      // 1. Carregar template HTML
      std::string htmlTemplate = loadHtmlTemplate(htmlTemplatePath);

      // 2. Substituir placeholders
      std::string htmlBody = replacePlaceholders(htmlTemplate, email.toName, email.body);

      // 3. Criar corpo do email
      std::string mailText = "To: \"" + email.toName + "\" <" + email.toAddress + ">\r\n"
                            + "Subject: " + email.subject + "\r\n"
                            + "\r\n" + htmlBody + "\r\n";

      curl_easy_setopt(curl, CURLOPT_URL, smtp_server.c_str());
      curl_easy_setopt(curl, CURLOPT_USERNAME, smtp_user.c_str());
      curl_easy_setopt(curl, CURLOPT_PASSWORD, smtp_password.c_str());

      curl_easy_setopt(curl, CURLOPT_MAIL_FROM, ("<" + email.fromAddress + ">").c_str());
      curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, curl_slist_append(NULL, recipients.c_str()));

      curl_easy_setopt(curl, CURLOPT_READFUNCTION, discard_data);
      curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
      curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
      curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "EHLO localhost");
      curl_easy_setopt(curl, CURLOPT_INFILESIZE, mailText.length());
      curl_easy_setopt(curl, CURLOPT_READDATA, mailText.c_str());
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);

      res = curl_easy_perform(curl);
      if(res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
      }
    } catch(const std::runtime_error& e){
      std::cerr << "Error: " << e.what() << std::endl;
      curl_global_cleanup();
      return false;
    }

    curl_slist_free_all(headerlist);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return res == CURLE_OK;
  } else {
    curl_global_cleanup();
    return false;
  }
}

void Mail::Setup() {
  // 1. Dados do Email (Configuração e conteúdo)
  EmailData email;
  email.fromAddress = "";
  email.fromName = "Seu App";
  email.toAddress = "usuario@example.com";
  email.toName = "Usuário Teste";
  email.subject = "Seu Código de Verificação";

  // 2. Geração do Código
  std::string verificationCode = generateVerificationCode(6);
  email.body = verificationCode; // O código vai no 'body', que será usado no template

  // 3. Configurações SMTP (Substitua com suas credenciais)
  std::string smtp_server = "smtp://seu_servidor_smtp:587";
  std::string smtp_user = "seu_usuario_smtp";
  std::string smtp_password = "sua_senha_smtp";

  // 4. Caminho para o template HTML
  std::string htmlTemplatePath = "index.html";

  // 5. Envio do Email (Agora com o path do template)
  if (sendEmail(email, smtp_server, smtp_user, smtp_password, htmlTemplatePath)) {
    std::cout << "E-mail enviado com sucesso!" << std::endl;
  } else {
    std::cerr << "Falha ao enviar o e-mail." << std::endl;
  }
}