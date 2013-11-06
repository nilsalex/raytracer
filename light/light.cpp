#include "light/light.hpp"

Light::Light(void)
  : point_(Vector(0.0, 0.0, 0.0)),
    colour_(RGBColour(0.0, 0.0, 0.0)) {}

Light::Light(Vector const& point, RGBColour const& colour)
  : point_(point), colour_(colour) {}

Light::Light(Light const& light)
  : point_(light.point_), colour_(light.colour_) {}

Light::~Light(void) {}

void Light::set_position(Vector const& point) {
  point_ = point;
}

Vector Light::get_position(void) const {
  return point_;
}

void Light::set_colour(RGBColour const& colour) {
  colour_ = colour;
}

RGBColour Light::get_colour(void) const {
  return colour_;
}
