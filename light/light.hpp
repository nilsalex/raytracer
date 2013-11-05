#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "colour/rgb_colour.hpp"
#include "math/vector.hpp"

class Light {
  private:
    Vector point_;
    RGBColour colour_;

  public:
    Light(void);
    Light(Vector const& point, RGBColour const& colour);
    Light(Light const& light);
    ~Light(void);

    void set_position(Vector const& v);
    Vector get_position(void) const;
    void set_colour(RGBColour const& colour);
    RGBColour get_colour(void) const;
};

#endif
