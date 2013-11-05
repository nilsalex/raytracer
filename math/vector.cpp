#include "math/vector.hpp"

#include <math.h>

Vector::Vector(void) : x_(0.0), y_(0.0), z_(0.0) {}

Vector::Vector(Vector const& other)
    : x_(other.get_x()), y_(other.get_y()), z_(other.get_z()) {}

Vector::Vector(double const& x, double const& y, double const& z)
    : x_(x), y_(y), z_(z) {}

Vector::~Vector(void) {}

double Vector::get_x(void) const {
  return x_;
}

double Vector::get_y(void) const {
  return y_;
}

double Vector::get_z(void) const {
  return z_;
}

void Vector::set_x(double const& x) {
  x_ = x;
}

void Vector::set_y(double const& y) {
  y_ = y;
}

void Vector::set_z(double const& z) {
  z_ = z;
}

Vector& Vector::operator= (Vector const& v) {
  if (this == &v) {
    return (*this);
  }
  x_ = v.get_x();
  y_ = v.get_y();
  z_ = v.get_z();
  return (*this);
}

Vector Vector::operator+ (Vector const& v) const {
  return Vector( x_ + v.get_x(), y_ + v.get_y(), z_ + v.get_z() );
}

Vector Vector::operator- (Vector const& v) const {
  return Vector( x_ - v.get_x(), y_ - v.get_y(), z_ - v.get_z() );
}

Vector Vector::operator* (double const& d) const {
  return Vector( d * x_, d * y_, d * z_ );
}

Vector Vector::operator/ (double const& d) const {
  return Vector( x_ / d, y_ / d, z_ / d );
}

double Vector::operator* (Vector const& v) const {
  return x_*v.get_x() + y_*v.get_y() + z_*v.get_z();
}

Vector Vector::Cross(Vector const& v) const {
  return Vector( y_*v.get_z() - z_*v.get_y(), z_*v.get_x() - x_*v.get_z(), x_*v.get_y() - y_*v.get_x() );
}

double Vector::Length(void) const {
  return sqrt( x_*x_ + y_*y_ + z_*z_ );
}

void Vector::Normalize(void) {
  double length = sqrt( x_*x_ + y_*y_ + z_*z_ );
  x_ = x_ / length;
  y_ = y_ / length;
  z_ = z_ / length;
}
