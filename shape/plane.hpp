#ifndef PLANE_HPP
#define PLANE_HPP

#include "shape/shape.hpp"
#include "math/vector.hpp"
#include "math/ray.hpp"

class Plane : public Shape {
  private:
    Vector point_;
    Vector normal_;

  public:
    Plane(void);
    Plane(Vector const& point, Vector const& normal);
    Plane(Plane const& plane);
    ~Plane(void);

    void set_point(Vector const& v);
    Vector get_point(void) const;
    void set_normal_vector(Vector const& v);
    Vector get_normal_vector(void) const;
    void const set_position(double const& X, double const& Y, double const& Z);
    Vector const get_position(void) const;
    bool Hit(Ray &ray, double &t) const;
};

#endif
