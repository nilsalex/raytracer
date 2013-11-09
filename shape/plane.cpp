#include "shape/plane.hpp"
#include <cmath>
#include <stdio.h>

Plane::Plane(void)
  : Shape(), point_(Vector(0.0, 0.0, 0.0)), normal_(Vector(0.0, 0.0, 0.0)),
    grid(Grid()), has_grid(false) {}

Plane::Plane(Vector const& point, Vector const& normal)
  : Shape(), point_(point), normal_(normal), grid(Grid()), has_grid(false) {
  if (get_material()->get_transparency() > 0.0) {
    get_material()->set_transparency(0.0);
  }
}

Plane::Plane(Vector const& point, Vector const& normal,
             Vector const& orientation_1, Vector const& orientation_2,
             double const& width, double const& thickness, Material* material)
  : Shape(), point_(point), normal_(normal),
    grid(Grid(orientation_1, orientation_2, width, thickness, material)),
    has_grid(true) {
  if (get_material()->get_transparency() > 0.0) {
    get_material()->set_transparency(0.0);
  }
}

Plane::Plane(Plane const& plane)
  : Shape(plane), point_(plane.point_), normal_(plane.normal_),
    grid(plane.grid), has_grid(plane.has_grid) {}

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

void Plane::set_grid_orientation_1(Vector const& v) {
  grid.orientation_1 = v;
}

Vector Plane::get_grid_orientation_1(void) const {
  return grid.orientation_1;
}

void Plane::set_grid_orientation_2(Vector const& v) {
  grid.orientation_2 = v;
}

Vector Plane::get_grid_orientation_2(void) const {
  return grid.orientation_2;
}

void Plane::set_grid_width(double const& d) {
  grid.width = d;
}

double Plane::get_grid_width(void) const {
  return grid.width;
}

void Plane::set_grid_thickness(double const& d) {
  grid.thickness = d;
}

double Plane::get_grid_thickness(void) const{
  return grid.thickness;
}

void Plane::set_grid_material(Material* material) {
  grid.material = material;
}

Material* Plane::get_grid_material(void) const {
  return grid.material;
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
    if (has_grid) {
      double x = std::abs(grid.orientation_1 * (ray.hit_info.position - point_));
      double y = std::abs(grid.orientation_2 * (ray.hit_info.position - point_));
      x = std::fmod(x, grid.width);
      y = std::fmod(y, grid.width);
      if (x <= grid.thickness/2 || y <= grid.thickness/2) {
        ray.hit_info.material = grid.material;
      } else {
        ray.hit_info.material = get_material();
      }
    } else {
      ray.hit_info.material = get_material();
    }
    ray.hit_info.distance = t;
    return true;
  }

  return false;
} 
