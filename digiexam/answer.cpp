#include <iostream>

// 7. Smart Pointer
class SmartPointer {
    int *ptr;
  public:
    // spara riktiga pointern
    SmartPointer(int *ptr) {
      this->ptr = ptr;
    }
    // automatisk deallokering av riktiga pointern
    ~SmartPointer() {
      delete (this->ptr);
    }

    // operatorn * 
    int& operator*() {
      return *this->ptr;
    }
};

void f1();
void f2();
int *f3();

int main() {
  int *p;

  int b = 10;

  p = &b;

  std::cout << "Värdet på pekaren p: " << *p << std::endl;


  int *p2;
  // p2 blir en dinglande pekare
  //p2 = f3();

  SmartPointer sp(new int());
  *sp = 20;
  std::cout << *sp;

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
int *f3() {
  // a finns inte i minne efter exec av funktionen
  int a = 10;
  return &a;
}

