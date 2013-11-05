#include "material/material.hpp"

Material::Material(void)
  : gloss_(2.0),
    transparency_(0.0),
    reflection_(0.0),
    refraction_in_(0.0),
    refraction_out_(0.0),
    colour_(0.0, 0.0, 0.0) {}

Material::~Material(void) {}

double Material::get_gloss(void) const {
  return gloss_;
}

void Material::set_gloss(double const& gloss) {
  gloss_ = gloss;
}

double Material::get_transparency(void) const {
  return transparency_;
}

void Material::set_transparency(double const& transparency) {
  transparency_ = transparency;
}

double Material::get_reflection(void) const {
  return reflection_;
}

void Material::set_reflection(double const& reflection) {
  reflection_ = reflection;
}

double Material::get_refraction_in(void) const {
  return refraction_in_;
}

void Material::set_refraction_in(double const& refraction_in) {
  refraction_in_ = refraction_in;
}

double Material::get_refraction_out(void) const {
  return refraction_out_;
}

void Material::set_refraction_out(double const& refraction_out) {
  refraction_out_ = refraction_out;
}

bool Material::HasTexture(void) const {
  return false;
}

RGBColour Material::get_colour(void) const {
  return colour_;
}

void Material::set_colour(RGBColour const& colour) {
  colour_ = colour;
}
