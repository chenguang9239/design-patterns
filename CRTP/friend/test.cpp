#include <iostream>

template <class T>
class Base {
 public:
  void interface() {
    // ...
    static_cast<T *>(this)->implementation();
    // ...
  }

  static void static_func() {
    // ...
    T::static_sub_func();
    // ...
  }

 private:
  Base(){};
  friend T;
};

class Derived : public Base<Derived> {
 public:
  void implementation();
  static void static_sub_func();
};

void Derived::implementation() {
  std::cout << "Derived implementation" << std::endl;
}

void Derived::static_sub_func() {}

class Derived1 : public Base<Derived> {
 public:
  int a;
  int b;
  int c;
  char d;
  void implementation();
  static void static_sub_func();
};

void Derived1::implementation() {
  std::cout << "Derived1 implementation" << std::endl;
}

void Derived1::static_sub_func() {}

int main() {
  {
    Derived d;
    d.interface();

    Base<Derived> &b = d;
    b.interface();

    Base<Derived> *bp = &d;
    bp->interface();
  }

  { Derived1 d; }

  return 0;
}
