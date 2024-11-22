#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <variant>

class YamlParser {
  private:
    std::unordered_map<std::string, std::variant<std::string, std::vector<std::string>>> key_value_list;
  public:
    YamlParser(const std::string fp);
    ~YamlParser();
    std::string getString(const std::string key);
    int getInt(const std::string key);
    std::vector<std::string> getStringList(const std::string key);
};

// load file and handle errors
YamlParser::YamlParser(const std::string fp) {

  std::string line;
  std::ifstream file(fp);

  std::string key;
  std::string value;
  std::vector<std::string> v_value;

  while(std::getline(file, line)) {
    // remove whitespaces
    for (int i = line.length(); i >= 0; i--) {
      if (line[i] == ' ') {
        line.erase(i, 1);
      }
    }

    // look for key
    int key_pos = line.find(":");
    if (key_pos != -1) {
      key = line.substr(0, key_pos);
      // look for single value
      value = line.substr(key_pos+1, line.length());
    }



    // look for multiple values
    if (line[0] == '-') {
      v_value.push_back(line.substr(1, line.length()));
    }

    // append
    if (value.length()) {
      this->key_value_list[key] = value;
    } else {
      this->key_value_list[key] = v_value;
    }

  }

  file.close();
}

YamlParser::~YamlParser() {}

// extract string from yaml-file
std::string YamlParser::getString(const std::string key) {
  return std::get<std::string>(this->key_value_list[key]);
}

// extract int from yaml-file
int YamlParser::getInt(const std::string key) {
  return std::stoi(std::get<std::string>(this->key_value_list[key]));
}

// extract list from yaml-file
std::vector<std::string> YamlParser::getStringList(const std::string key) {
  return std::get<std::vector<std::string>>(this->key_value_list[key]);
}

int main() {
  YamlParser parser("yaml-file.yml");

  std::string name = parser.getString("name");
  int age = parser.getInt("age");
  std::vector<std::string> items = parser.getStringList("items");

  std::cout << name << std::endl;
  std::cout << age << std::endl;
  for (const auto& item : items) {
    std::cout << item << std::endl;
  }

  return 0;
}
