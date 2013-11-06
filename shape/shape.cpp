#include "shape.hpp"

Shape::Shape(void)
  : material_(0), angle_(0.0) {}
// Path...

Shape::Shape(Shape const& shape) {
  if (shape.material_) {
    material_ = shape.material_;
  } else {
    material_ = 0;
  }
// Path...
}

Shape::~Shape(void) {
  if (material_) {
    delete material_;
  }
  material_ = 0;
// Path...
}

void Shape::set_material(Material *material) {
  material_ = material;
}

Material* Shape::get_material(void) const {
  return material_;
}

void Shape::set_start_angle(double const& angle) {
  angle_ = angle;
}

double Shape::get_start_angle(void) const {
  return angle_;
}
