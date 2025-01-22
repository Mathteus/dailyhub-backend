#ifndef REST_CLIENT_HPP
#define REST_CLIENT_HPP

#include <string>
#include <map>
#include <curl/curl.h>
#include "spdlog/spdlog.h"
#include "utility.hpp"

class RestClient {
public:
  RestClient(std::string baseUrl);
  ~RestClient();

  void setBasicAuth(const std::map<std::string, std::string>& basic_auth);

  // Métodos para diferentes tipos de requisições
  std::string get(const std::string& url, const std::map<std::string, std::string>& headers = {});
  std::string post(const std::string& url, const std::string& body, const std::map<std::string, std::string>& headers = {});
  std::string put(const std::string& url, const std::string& body, const std::map<std::string, std::string>& headers = {});
  std::string patch(const std::string& url, const std::string& body, const std::map<std::string, std::string>& headers = {});
  std::string deleteRequest(const std::string& url, const std::map<std::string, std::string>& headers = {});

private:
  CURL* curl;
  CURLcode res;
  std::string _base_url;
  std::map<std::string, std::string> basicAuth;
  
  // Callback para receber dados da resposta
  static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);

  // Método para executar a requisição
  std::string executeRequest(const std::string& url, const std::string& method, const std::string& body, const std::map<std::string, std::string>& headers);
  
  //Método para adicionar os headers na request
  void addHeaders(const std::map<std::string, std::string>& headers);
  const char* CreateBasicAuth();
};

#endif