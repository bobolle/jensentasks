#include <iostream>

void f1();
void f2();
int f3();

int main() {
  int *p;

  int b = 10;

  p = &b;

  std::cout << "Värdet på pekaren p: " << *p;


  int *p2;
  // p2 blir en dinglande pekare
  p2 = f3();

  return 0;
}

// Question 6 - Minneshanteringsproblem
// 1. Minnesläckor
void f1() {
  // den här frigörs aldrig
  int *p = (int*) malloc(1);
  return;
}

// 2. Dubbel Frigörning
void f2() {
  // den här frigörs två gånger
  int *p = (int*) malloc(1);
  free(p);
  free(p);
  return;
}

// 3. Dangling pointer
int f3() {
  // a finns inte i minne efter exec av funktionen
  int a = 10;
  return &a;
}
