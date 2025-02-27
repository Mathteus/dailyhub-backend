#include "Dailyhub/Core/utility.hpp"
#include <iomanip>

uint32_t Dailyhub::Core::Utility::Integer(std::string str) {
  return static_cast<uint32_t>(std::atoi(str.c_str()));
}

std::string Dailyhub::Core::Utility::String(int32_t num) {
  return std::to_string(num);
}

int Dailyhub::Core::Utility::random(int32_t min, int32_t max) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max);
  return dist6(rng);
}

int Dailyhub::Core::Utility::random(uint32_t max) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(0, max);
  return dist6(rng);
}

std::string Dailyhub::Core::Utility::bytes_to_hex_string(const std::vector<unsigned char>& bytes) {
  std::stringstream ss;
  ss << std::hex << std::setfill('0');
  for (const unsigned char byte : bytes) {
    ss << std::setw(2) << static_cast<int>(byte);
  }
  return ss.str();
}

std::string Dailyhub::Core::Utility::time_point_to_string(const std::chrono::system_clock::time_point& tp) {
  std::time_t t = std::chrono::system_clock::to_time_t(tp);
  std::tm tm = *std::gmtime(&t); // Ou std::localtime para o timezone local
  std::stringstream ss;
  ss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%SZ"); // Formato ISO 8601
  return ss.str();
}

std::chrono::system_clock::time_point Dailyhub::Core::Utility::parse_date_time(const std::string& time_str) {
  std::chrono::system_clock::time_point tp;
  std::stringstream ss(time_str);
  date::from_stream(ss, "%Y-%m-%dT%H:%M:%SZ", tp);
  if (ss.fail()) {
    throw std::runtime_error("Falha ao analisar a data e hora");
  }
  return tp;
}

std::string Dailyhub::Core::Utility::gerateString(const uint8_t lenght = 6) {
  const std::string caracters{"0123654789MNBVCXZLKJHGFDSAPOIUYTREWQ"};
  std::string randomString;
  for (size_t i = 0; i <lenght; i++) {
    randomString += caracters[random(caracters.size())];
  }

  return randomString;
}

const char* Dailyhub::Core::Utility::gerateStringC(const uint8_t lenght = 6) {
  const std::string caracters{"0123654789MNBVCXZLKJHGFDSAPOIUYTREWQ"};
  std::string randomString;
  for (size_t i = 0; i <lenght; i++) {
    randomString += caracters[random(caracters.size())];
  }

  const char* c_str = randomString.c_str();
  return c_str;
}

std::string Dailyhub::Core::Utility::gerateCode(int seed) {
  std::mt19937 gen(seed);
  std::uniform_int_distribution dis(0, 999999);
  return std::to_string(dis(gen));
}

std::string Dailyhub::Core::Utility::base64_encode(const std::string& input) {
  const std::string base64_chars{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};
  std::string encoded;
  int32_t i = 0;
  uint8_t char_array_3[3];
  uint8_t char_array_4[4];
  size_t input_length = input.length();

  for (size_t in_i = 0; in_i < input_length;) {
    char_array_3[0] = input[in_i++];
    char_array_3[1] = (in_i < input_length) ? input[in_i++] : 0;
    char_array_3[2] = (in_i < input_length) ? input[in_i++] : 0;

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (i = 0; i < 4; ++i) {
      if (in_i <= input_length && char_array_4[i] < 64) {
        encoded += base64_chars[char_array_4[i]];
      } else {
        encoded += '=';
      }
    }
  }

  return encoded;
}

std::string Dailyhub::Core::Utility::base64_decode(const std::string& input) {
  const std::string base64_chars{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};
  std::string decoded;
  int32_t i = 0;
  uint8_t char_array_3[3];
  uint8_t char_array_4[4];
  size_t input_length = input.size();

  for (size_t in_i = 0; in_i < input_length;) {
    for (i = 0; i < 4; ++i) {
      char_array_4[i] = 0;
      while (in_i < input_length && (base64_chars.find(input[in_i]) == std::string::npos) && input[in_i] != '=') {
        in_i++;
      }

      if (in_i < input_length) {
        if(input[in_i] != '='){
          char_array_4[i] = base64_chars.find(input[in_i]);
        }
        in_i++;
      }
    }

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
    
    for (i = 0; i < 3; ++i) {
      if (char_array_3[i] != 0) {
        decoded += char_array_3[i];
      }
    }

  }
  return decoded;
}

bool Dailyhub::Core::Utility::IsValidEmail(const std::string& email) {
  const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
  return !std::regex_match(email, pattern);
}

bool Dailyhub::Core::Utility::ContainsSymbols(const std::string& str) {
  for (const char c : str) {
    if (!isalnum(c)) {
      if (!isspace(c)) {
        return true;
      }
    }
  }
  return false;
}

std::string Dailyhub::Core::Utility::readFilesSQL(const std::string& sqlFile) {
  std::ifstream file(sqlFile, std::ios::in | std::ios::binary);
  if (!file.is_open()) {
    spdlog::error("Erro ao abrir o SQL: {}", sqlFile);
    return{""};
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

std::string Dailyhub::Core::Utility::replaceTemplates(std::string html, const std::unordered_map<std::string, std::string>& replacements) {
  if (html.empty() || replacements.empty()) {
    return "";
  }

  std::regex templateRegex{R"(\{\{\s*(\w+)\s*\}\})"};
  std::string result;
  std::sregex_iterator it{html.begin(), html.end(), templateRegex};
  std::sregex_iterator end;
  size_t lastMatchEnd = 0;

  while (it != end) {
    std::smatch match = *it;
    size_t matchPos = match.position();
    result += html.substr(lastMatchEnd, matchPos - lastMatchEnd); // Adiciona tudo que esta antes do template na string de resultado
    std::string templateKey = match[1].str();  // Retira o nome do template (o que esta entre as chaves)

    if (replacements.count(templateKey)) {
      result += replacements.at(templateKey); // se o templateKey existir no unordered_map, adicione a string substituida
    } else {
      result += match.str(); //se o templateKey não existir no unordered_map, adicione o template original
    }

    lastMatchEnd = matchPos + match.length(); // atualiza a posição do ultimo match
    it++;
  }

  result += html.substr(lastMatchEnd); // adicione o resto do html que sobrou da string original
  return result;
}

std::string Dailyhub::Core::Utility::readFile(const std::string& filename, const std::unordered_map<std::string, std::string>& replacements) {
  std::ifstream file{std::string(filename), std::ios::in | std::ios::binary};
  if (!file.is_open()) {
    std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
    return "";
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  return Dailyhub::Core::Utility::replaceTemplates(buffer.str(), replacements);
}
