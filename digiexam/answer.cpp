#include <iostream>

int main() {
  int *p;

  int b = 10;

  p = &b;

  std::cout << "Värdet på pekaren p: " << *p;

  return 0;
}
