#include "shape/tiled_plane.hpp"
#include <cmath>
#include <stdio.h>

TiledPlane::TiledPlane(void)
  : Plane(), unit_1_(Vector()), unit_2_(Vector()) {}

TiledPlane::TiledPlane(Vector const& point, Vector const& normal)
  : Plane(point, normal), unit_1_(Vector()), unit_2_(Vector()), material_t_(0) {
  if (get_material()->get_transparency() > 0.0) {
    get_material()->set_transparency(0.0);
  }
}

TiledPlane::TiledPlane(TiledPlane const& plane)
  : Plane(plane), unit_1_(plane.unit_1_), unit_2_(plane.unit_2_), material_t_(plane.material_t_) {}

TiledPlane::~TiledPlane(void) {}

void TiledPlane::set_unit_1(Vector const& v) {
  unit_1_ = v;
}

Vector TiledPlane::get_unit_1(void) const {
  return unit_1_;
}

void TiledPlane::set_unit_2(Vector const& v) {
  unit_2_ = v;
}

Vector TiledPlane::get_unit_2(void) const {
  return unit_2_;
}

void TiledPlane::set_material_t(Material* material) {
  material_t_ = material;
}

Material* TiledPlane::get_material_t(void) const {
  return material_t_;
}

bool TiledPlane::Hit(Ray &ray, double &t) const {
  double d = ray.get_direction() * this->get_normal_vector();
  if (d >= 0.0) {
    return false;
  }

  d = ((this->get_point() - ray.get_origin()) * this->get_normal_vector()) / d;
  if ((d > SHAPE_EPSILON) && (d < t)) {
    t = d;
    ray.hit_info.position = ray.get_origin() + (ray.get_direction() * t);
    ray.hit_info.normal = this->get_normal_vector();
    ray.hit_info.material = get_material();
    ray.hit_info.distance = t;
    return true;
  }

  return false;
} 
