#include <iostream>
#include <utility>

// create a program that uses a pair to store the name and age of three different people.
// display their details using the first and second members.
int main() {
    std::pair<std::string, int> name_age = std::make_pair("Tom", 10);
    std::cout << "name: " << name_age.first << ", age: " << name_age.second << std::endl;

    return 0;
}
