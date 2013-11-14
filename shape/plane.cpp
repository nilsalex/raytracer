#include "shape/plane.hpp"
#include <cmath>
#include <stdio.h>

Plane::Plane(void)
  : Shape(), point_(Vector(0.0, 0.0, 0.0)), normal_(Vector(0.0, 0.0, 0.0)) {}

Plane::Plane(Vector const& point, Vector const& normal)
  : Shape(), point_(point), normal_(normal) {
  if (get_material()->get_transparency() > 0.0) {
    get_material()->set_transparency(0.0);
  }
}

Plane::Plane(Plane const& plane)
  : Shape(plane), point_(plane.point_), normal_(plane.normal_) {}

Plane::~Plane(void) {}

void Plane::set_point(Vector const& v) {
  point_ = v;
}

Vector Plane::get_point(void) const {
  return point_;
}

void Plane::set_normal_vector(Vector const& v) {
  normal_ = v;
}

Vector Plane::get_normal_vector(void) const {
  return normal_;
}

void Plane::set_position(double const& X, double const& Y, double const& Z) {
  set_point(Vector(X, Y, Z));
}

Vector Plane::get_position(void) const {
  return point_;
}

bool Plane::Hit(Ray &ray, double &t) const {
  double d = ray.get_direction() * normal_;
  if (d >= 0.0) {
    return false;
  }

  d = ((point_ - ray.get_origin()) * normal_) / d;
  if ((d > SHAPE_EPSILON) && (d < t)) {
    t = d;
    ray.hit_info.position = ray.get_origin() + (ray.get_direction() * t);
    ray.hit_info.normal = normal_;
    ray.hit_info.material = get_material();
    ray.hit_info.distance = t;
    return true;
  }

  return false;
} 
