#include "math/ray.hpp"

Ray::Ray(Vector const& origin, Vector const& direction)
  : origin_(origin),
    direction_(direction) {}

Ray::~Ray(void) {}

Vector Ray::Evaluate(double const& t) const {
  return origin_ + direction_ * t;
}
