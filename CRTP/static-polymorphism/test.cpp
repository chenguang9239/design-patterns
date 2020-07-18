#include <iostream>

template <class T>
struct Base {
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
};

struct Derived : Base<Derived> {
  void implementation();
  static void static_sub_func();
};

void Derived::implementation() {
  std::cout << "Derived implementation" << std::endl;
}

void Derived::static_sub_func() {}

int main() {
  Derived d;
  d.interface();

  Base<Derived> &b = d;
  b.interface();

  Base<Derived> *bp = &d;
  bp->interface();
  return 0;
}
