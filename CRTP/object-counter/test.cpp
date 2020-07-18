#include <iostream>

template <typename T>
struct counter {
  static int objects_created;
  static int objects_alive;

  counter() {
    ++objects_created;
    ++objects_alive;
  }

  counter(const counter &) {
    ++objects_created;
    ++objects_alive;
  }

 protected:
  ~counter()  // objects should never be removed through pointers of this type
  {
    --objects_alive;
  }
};

template <typename T>
int counter<T>::objects_created = 0;

template <typename T>
int counter<T>::objects_alive = 0;

class X : public counter<X> {
  // ...
};

class Y : public counter<Y> {
  // ...
};

int main() {
  {
    X x1;
    std::cout << "X alive count: " << X::objects_alive
              << ", X created count: " << X::objects_created << std::endl
              << "Y alive count: " << Y::objects_alive
              << ", Y created count: " << Y::objects_created << std::endl;
  }

  std::cout << "X alive count: " << X::objects_alive
            << ", X created count: " << X::objects_created << std::endl
            << "Y alive count: " << Y::objects_alive
            << ", Y created count: " << Y::objects_created << std::endl;

  {
    Y y1;
    std::cout << "X alive count: " << X::objects_alive
              << ", X created count: " << X::objects_created << std::endl
              << "Y alive count: " << Y::objects_alive
              << ", Y created count: " << Y::objects_created << std::endl;
  }

  std::cout << "X alive count: " << X::objects_alive
            << ", X created count: " << X::objects_created << std::endl
            << "Y alive count: " << Y::objects_alive
            << ", Y created count: " << Y::objects_created << std::endl;

  return 0;
}
