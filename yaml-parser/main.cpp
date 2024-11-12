#include <iostream>
#include <vector>
#include <unordered_map>
#include <variant>
#include <cstdio>

class YamlParser {
  private:
    std::unordered_map<std::string, std::variant<int, std::string, std::vector<std::string>>> key_value_list;
  public:
    YamlParser(const char* filename);
    ~YamlParser();
    std::string getString(std::string key);
    int getInt(std::string key);
    std::vector<std::string> getStringList(std::string key);
};

// load file and handle errors
YamlParser::YamlParser(const char* filename) {
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    std::cerr << "error, failed to open file.\n";
  } else {

    char line[50];

    while (fgets(line, sizeof(line), file) != NULL) {
      std::cout << line;
    }

    // search for "string"
    // after : search for value
    // if - after :
    // make it a list

    

    fclose(file);
  }
}

YamlParser::~YamlParser() {}

// extract string from yaml-file
std::string YamlParser::getString(std::string key) {
  return std::get<std::string>(this->key_value_list[key]);
}

// extract int from yaml-file
int YamlParser::getInt(std::string key) {
  return std::get<int>(this->key_value_list[key]);
}

// extract list from yaml-file
std::vector<std::string> YamlParser::getStringList(std::string key) {
  return std::get<std::vector<std::string>>(this->key_value_list[key]);
}

int main() {
  YamlParser parser("yaml-file.yml");

  std::string name;
  int age;
  std::vector<std::string> items;

  return 0;
}
