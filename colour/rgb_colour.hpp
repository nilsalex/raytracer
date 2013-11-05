#ifndef RGB_COLOUR_HPP
#define RGB_COLOUR_HPP

#include <math.h>

class RGBColour {
  private:
    double red_, green_, blue_;

  public:
    RGBColour(void);
    RGBColour(double const& r, double const& g, double const& b);
    RGBColour(RGBColour const& rgb);
    ~RGBColour(void);

    double get_red(void) const;
    void set_red(double const& red);
    double get_green(void) const;
    void set_green(double const& green);
    double get_blue(void) const;
    void set_blue(double const& blue);

    RGBColour& operator= (RGBColour const& rgb);
    RGBColour operator+ (RGBColour const& rgb) const;
    RGBColour operator+ (double const& d) const;
    RGBColour operator- (RGBColour const& rgb) const;
    RGBColour operator- (double const& d) const;
    RGBColour operator* (RGBColour const& rgb) const;
    RGBColour operator* (double const& d) const;
    RGBColour operator/ (double const& d) const;
    bool operator== (RGBColour const& rgb) const;
    RGBColour power(double const& p) const;
};

#endif
