#include <iostream>

using namespace std;

// Base class
template <typename ConcretePrinter>
class Printer {
 public:
  Printer(ostream& pstream) : m_stream(pstream) {}

  template <typename T>
  ConcretePrinter& print(T&& t) {
    m_stream << t;
    return static_cast<ConcretePrinter&>(*this);
  }

  template <typename T>
  ConcretePrinter& println(T&& t) {
    m_stream << t << endl;
    return static_cast<ConcretePrinter&>(*this);
  }

 private:
  ostream& m_stream;
};

// Derived class
class CoutPrinter : public Printer<CoutPrinter> {
 public:
  CoutPrinter() : Printer(cout) {}

  CoutPrinter& SetConsoleColor(int c) {
    // ...
    return *this;
  }
};

int main() {
  // usage
  CoutPrinter().print("Hello ").SetConsoleColor(0).println("Printer!");
  return 0;
}
