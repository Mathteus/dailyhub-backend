#include "rest_client.hpp"

RestClient::RestClient(std::string baseUrl): _base_url(baseUrl) {
  curl = curl_easy_init(); 
  if (!curl) {
    spdlog::error("Erro ao inicializar o cURL.\n");
  }
}

RestClient::~RestClient() {
  if (curl) {
    curl_easy_cleanup(curl);
  }
}

void RestClient::setBasicAuth(const std::map<std::string, std::string>& basic_auth) {
  basicAuth = std::move(basic_auth);
}

size_t RestClient::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
  size_t totalSize = size * nmemb;
  output->append((char*)contents, totalSize);
  return totalSize;
}

std::string RestClient::get(const std::string& url, const std::map<std::string, std::string>& headers) {
  return executeRequest(url, "GET", "", headers);
}

std::string RestClient::post(const std::string& url, const std::string& body, const std::map<std::string, std::string>& headers) {
  return executeRequest(url, "POST", body, headers);
}

std::string RestClient::put(const std::string& url, const std::string& body, const std::map<std::string, std::string>& headers) {
  return executeRequest(url, "PUT", body, headers);
}

std::string RestClient::patch(const std::string& url, const std::string& body, const std::map<std::string, std::string>& headers) {
  return executeRequest(url, "PATCH", body, headers);
}

std::string RestClient::deleteRequest(const std::string& url, const std::map<std::string, std::string>& headers) {
  return executeRequest(url, "DELETE", "", headers);
}

std::string RestClient::executeRequest(const std::string& url, const std::string& method, const std::string& body, const std::map<std::string, std::string>& headers) {
  std::string response;
  
  if (!curl) {
    return "Erro: cURL não inicializado.";
  }

  curl_easy_setopt(curl, CURLOPT_URL, std::string(_base_url + url).c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, RestClient::WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  addHeaders(headers);
    
  if (method == "POST" || method == "PUT" || method == "PATCH") {
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.size());
  }
    
  if (method != "GET") {
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());
  }

  res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    spdlog::error("Erro na requisição: {}\n", curl_easy_strerror(res));
    return "";
  }

  return response;
}

const char* RestClient::CreateBasicAuth() {
  if (basicAuth.empty()) {
    return "";
  }

  std::string auth = basicAuth["username"] + ":" + basicAuth["password"];
  return std::string("Authorization: Basic " + Utility::base64_encode(auth)).c_str();
}

void RestClient::addHeaders(const std::map<std::string, std::string>& headers){
  struct curl_slist *headerList = NULL;
  headerList = curl_slist_append(headerList, CreateBasicAuth());
  for (const auto& pair : headers) {
    std::string header = pair.first + ": " + pair.second;
    headerList = curl_slist_append(headerList, header.c_str());
  }
  
  if (headerList) {
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList);
  }
}