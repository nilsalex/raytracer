#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <math.h>
#include "math/vector.hpp"
#include "math/ray.hpp"
#include "shape/shape.hpp"
//#include "path/path.hpp"

class Sphere : public Shape {
  private:
    Vector center_;
    double radius_;

  public:
    Sphere(void);
    Sphere(Vector const& center, double const& radius);
    Sphere(Sphere const& sphere);
    ~Sphere(void);

    void set_center(Vector const& center);
    Vector get_center(void) const;
    void set_radius(double const& radius);
    double get_radius(void) const;
    void set_position(double const& X, double const& Y, double const& Z);
    Vector get_position(void) const;
    bool Hit(Ray &ray, double &t) const;
};

#endif
