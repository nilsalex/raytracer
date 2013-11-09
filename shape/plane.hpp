#ifndef PLANE_HPP
#define PLANE_HPP

#include "shape/shape.hpp"
#include "math/vector.hpp"
#include "math/ray.hpp"

class Plane : public Shape {
  private:
    Vector point_;
    Vector normal_;
    struct Grid {
      Vector orientation;
      double width, thickness;
      Grid(void) : orientation(Vector(0.0, 0.0, 0.0)),
                   width(0), thickness(0) {};
      Grid(Vector const& orientationp,
           double const& widthp, double const& thicknessp)
        : orientation(orientationp),
          width(widthp), thickness(thicknessp) {};
      ~Grid(void) {};
    } grid;

  public:
    Plane(void);
    Plane(Vector const& point, Vector const& normal);
    Plane(Vector const& point, Vector const& normal,
          Vector const& orientation, double const& width,
          double const& thickness);
    Plane(Plane const& plane);
    ~Plane(void);

    void set_point(Vector const& v);
    Vector get_point(void) const;
    void set_normal_vector(Vector const& v);
    Vector get_normal_vector(void) const;
    void set_position(double const& X, double const& Y, double const& Z);
    Vector get_position(void) const;
    void set_grid_orientation(Vector const& v);
    Vector get_grid_orientation(void) const;
    void set_grid_width(double const& d);
    double get_grid_width(void) const;
    void set_grid_thickness(double const& d);
    double get_grid_thickness(void) const;
    bool Hit(Ray &ray, double &t) const;
};

#endif
