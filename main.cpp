#include <iostream>

#include "math/ray.hpp"

int main() {
  Vector test_o, test_d;
  test_d.set_x(2.3);
  test_o.set_x(-1);
  Ray test(test_o, test_d);
  std::cout << test.Evaluate(1.5).get_x() << std::endl;
  return 0;
}
