#include "shape/sphere.hpp"

Sphere::Sphere(void)
  : Shape(), center_(Vector(0.0, 0.0, 0.0)), radius_(0.0) {}

Sphere::Sphere(Vector const& center, double const& radius)
  : Shape(), center_(center), radius_(radius) {}

Sphere::Sphere(Sphere const& sphere)
  : Shape(sphere), center_(sphere.center_), radius_(sphere.radius_) {}

Sphere::~Sphere(void) {}

void Sphere::set_center(Vector const& center) {
  center_ = center;
}

Vector Sphere::get_center(void) const {
  return center_;
}

void Sphere::set_radius(double const& radius) {
  radius_ = radius;
}

double Sphere::get_radius(void) const {
  return radius_;
}

void const Sphere::set_position(double const& X, double const& Y, double const& Z) {
  set_center(Vector(X, Y, Z));
}

Vector const Sphere::get_position(void) const {
  return center_;
}

const bool Sphere::Hit(Ray &ray, double &t) const {
  Vector dist = ray.get_origin() - center_;
  double a = ray.get_direction() * ray.get_direction();
  double b = ray.get_direction() * dist * 2.0;
  double c = dist * dist - radius_ * radius_;
  double D = b * b - 4.0 * a * c;

  bool is_hit = false;
  if (D >= 0.0) {
    double t0 = ( -b - sqrt(D) ) / (2.0 * a );
    double t1 = ( -b + sqrt(D) ) / (2.0 * a );
    if ((t0 > SHAPE_EPSILON) && (t0 < t)) {
      t = t0;
      is_hit = true;
    }
    if ((t1 > SHAPE_EPSILON) && (t1 < t)) {
      t = t1;
      is_hit = true;
    }

    if (is_hit) {
      ray.hit_info.position = ray.get_origin() + (ray.get_direction() * t);
      Vector normal = ray.hit_info.position - center;
      double temp = normal * normal;
      if (temp <= 0.0) {
        is_hit = false;
      } else {
        temp = 1.0 / sqrt(temp);
        ray.hit_info.normal = normal * temp;
        ray.hit_info.material = get_material();
        ray.hit_info.distance = t;
      }
    }
  }

  return is_hit;
}
