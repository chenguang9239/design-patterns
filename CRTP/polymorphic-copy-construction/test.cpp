#include <iostream>
#include <memory>
#include <vector>

// Base class has a pure virtual function for cloning
class AbstractShape {
 public:
  virtual ~AbstractShape() = default;
  virtual std::shared_ptr<AbstractShape> clone() const = 0;
  virtual void ShowShape() = 0;
};

// This CRTP class implements clone() for Derived
template <typename Derived>
class Shape : public AbstractShape {
 public:
  std::shared_ptr<AbstractShape> clone() const override {
    std::cout << "CRTP Shape clone..." << std::endl;
    return std::make_shared<Derived>(static_cast<Derived const&>(*this));
  }

 protected:
  // We make clear Shape class needs to be inherited
  Shape() = default;
  Shape(const Shape&) = default;
};

// Every derived class inherits from CRTP class instead of abstract class

class Square : public Shape<Square> {
 public:
  Square() { std::cout << "Square constructor" << std::endl; }
  Square(const Square&) { std::cout << "Square copy constructor" << std::endl; }
  virtual void ShowShape() override { std::cout << "Square" << std::endl; }
};

class Circle : public Shape<Circle> {
 public:
  Circle() { std::cout << "Circle constructor" << std::endl; }
  Circle(const Circle&) { std::cout << "Circle copy constructor" << std::endl; }
  virtual void ShowShape() override { std::cout << "Circle" << std::endl; }
};

int main() {
  std::vector<AbstractShape*> abstract_nodes;
  abstract_nodes.push_back(new Square());
  abstract_nodes.push_back(new Circle());

  auto abs_p1 = abstract_nodes[0];
  auto abs_p2 = abstract_nodes[1];

  abs_p1->ShowShape();
  abs_p2->ShowShape();

  auto square_uptr = abs_p1->clone();
  auto circle_uptr = abs_p2->clone();

  square_uptr->ShowShape();
  circle_uptr->ShowShape();

  return 0;
}
