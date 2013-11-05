#include "math/ray.hpp"

Ray::Ray()
  : origin_(0.0, 0.0, 0.0),
    direction_(0.0, 0.0, 0.0) {}

Ray::Ray(Vector const& origin, Vector const& direction)
  : origin_(origin),
    direction_(direction) {}

Ray::Ray(Ray const& ray)
  : origin_(ray.get_origin()),
    direction_(ray.get_direction()) {}

Ray::~Ray(void) {}

Vector Ray::get_origin(void) const {
  return origin_;
}

void Ray::set_origin(Vector const& origin) {
  origin_ = origin;
}

Vector Ray::get_direction(void) const {
  return direction_;
}

void Ray::set_direction(Vector const& direction) {
  direction_ = direction;
}

Ray& Ray::operator= (Ray const& ray) {
  if (this == &ray) {
    return (*this);
  }
  origin_ = ray.get_origin();
  direction_ = ray.get_direction();

  return (*this);
}
