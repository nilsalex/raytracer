#include <iostream>

#include "math/ray.hpp"

int main() {
  Vector test_o, test_d;
  test_d.set_x(2.3);
  test_o.set_x(-1);
  Ray test(test_o, test_d);
  return 0;
}
