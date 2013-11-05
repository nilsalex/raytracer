#include "colour/rgb_colour.hpp"

RGBColour::RGBColour(void)
  : red_(0.0), green_(0.0), blue_(0.0) {}

RGBColour::RGBColour(double const& r, double const& g, double const& b)
  : red_(r), green_(g), blue_(b) {}

RGBColour::RGBColour(RGBColour const& rgb)
  : red_(rgb.get_red()),
    green_(rgb.get_green()),
    blue_(rgb.get_blue()) {}

RGBColour::~RGBColour(void) {}

double RGBColour::get_red(void) const {
  return red_;
}

void RGBColour::set_red(double const& red) {
  red_ = red;
}

double RGBColour::get_green(void) const {
  return green_;
}

void RGBColour::set_green(double const& green) {
  green_ = green;
}

double RGBColour::get_blue(void) const {
  return blue_;
}

void RGBColour::set_blue(double const& blue) {
  blue_ = blue;
}

RGBColour& RGBColour::operator= (RGBColour const& rgb) {
  if (this == &rgb) {
    return (*this);
  }
  red_ = rgb.get_red();
  green_ = rgb.get_green();
  blue_ = rgb.get_blue();

  return (*this);
}

RGBColour RGBColour::operator+ (RGBColour const& rgb) const {
  return ( RGBColour(red_ + rgb.get_red(), green_ + rgb.get_green(), blue_ + rgb.get_blue()) );
}

RGBColour RGBColour::operator+ (double const& d) const {
  return ( RGBColour(red_ + d, green_ + d, blue_ + d) );
}

RGBColour RGBColour::operator- (RGBColour const& rgb) const {
  return ( RGBColour(red_ - rgb.get_red(), green_ - rgb.get_green(), blue_ - rgb.get_blue()) );
}

RGBColour RGBColour::operator- (double const& d) const {
  return ( RGBColour(red_ - d, green_ - d, blue_ - d) );
}

RGBColour RGBColour::operator* (RGBColour const& rgb) const {
  return ( RGBColour(red_ * rgb.get_red(), green_ * rgb.get_green(), blue_ * rgb.get_blue()) );
}

RGBColour RGBColour::operator* (double const& d) const {
  return ( RGBColour(red_ * d, green_ * d, blue_ * d) );
}

RGBColour RGBColour::operator/ (double const& d) const {
  return ( RGBColour(red_ / d, green_ / d, blue_ / d) );
}

bool RGBColour::operator== (RGBColour const& rgb) const {
  return ( red_ == rgb.get_red()
        && green_ == rgb.get_green()
        && blue_ == rgb.get_blue() );
}

RGBColour RGBColour::power(double const& p) const {
  return ( RGBColour(pow(red_, p), pow(green_, p), pow(blue_, p)) );
}
