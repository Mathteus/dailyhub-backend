#include "Dailyhub/Core/utility.hpp"

uint32_t Utility::Integer(std::string str) {
  return static_cast<uint32_t>(std::atoi(str.c_str()));
}

std::string Utility::String(uint32_t num) {
  return std::to_string(num);
}

int Utility::random(int min, int max) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max);
  return dist6(rng);
}

int Utility::random(int max) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(0, max);
  return dist6(rng);
}

std::string Utility::gerateString() {
  std::string caracters = "0123654789MNBVCXZLKJHGFDSAPOIUYTREWQ";
  const size_t lenght = 6;
  std::string randomString;
  for (size_t i = 0; i <lenght; i++) {
    randomString += caracters[random(caracters.size())];
  }

  return randomString;
}

std::string Utility::gerateCode(int seed) {
  std::mt19937 gen(seed);
  std::uniform_int_distribution dis(0, 999999);
  return std::to_string(dis(gen));
}

time_t Utility::Date() {
  time_t timestamp;
  return timestamp;
}

std::string Utility::base64_encode(const std::string& input) {
  static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  std::string encoded;
  int i = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];
  size_t input_length = input.length();

  for (size_t in_i = 0; in_i < input_length; ) {
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

std::string Utility::base64_decode(const std::string& input) {
  static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  std::string decoded;
  int i = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];
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

std::string Utility::readFilesSQL(const std::string& sqlFile) {
  std::ifstream file(sqlFile, std::ios::in | std::ios::binary);
  if (!file.is_open()) {
    spdlog::error("Erro ao abrir o SQL: {}", sqlFile);
    return{""};
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}
