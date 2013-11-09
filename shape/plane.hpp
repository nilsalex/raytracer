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
      Vector orientation_1;
      Vector orientation_2;
      double width, thickness;
      Material* material;
      Grid(void) : orientation_1(Vector(0.0, 0.0, 0.0)),
                   orientation_2(Vector(0.0, 0.0, 0.0)),
                   width(0), thickness(0),
                   material(0) {};
      Grid(Vector const& orientation_1p,
           Vector const& orientation_2p,
           double const& widthp, double const& thicknessp,
           Material* materialp)
        : orientation_1(orientation_1p),
          orientation_2(orientation_2p),
          width(widthp), thickness(thicknessp),
          material(materialp) {};
      ~Grid(void) {
        if (material) {
          delete material;
        }
        material = 0;
      };
    } grid;

  public:
    Plane(void);
    Plane(Vector const& point, Vector const& normal);
    Plane(Vector const& point, Vector const& normal,
          Vector const& orientation_1, Vector const& orientation_2,
          double const& width, double const& thickness, Material* material);
    Plane(Plane const& plane);
    ~Plane(void);

    bool has_grid;

    void set_point(Vector const& v);
    Vector get_point(void) const;
    void set_normal_vector(Vector const& v);
    Vector get_normal_vector(void) const;
    void set_position(double const& X, double const& Y, double const& Z);
    Vector get_position(void) const;
    void set_grid_orientation_1(Vector const& v);
    Vector get_grid_orientation_1(void) const;
    void set_grid_orientation_2(Vector const& v);
    Vector get_grid_orientation_2(void) const;
    void set_grid_width(double const& d);
    double get_grid_width(void) const;
    void set_grid_thickness(double const& d);
    double get_grid_thickness(void) const;
    void set_grid_material(Material* material);
    Material* get_grid_material(void) const;
    bool Hit(Ray &ray, double &t) const;
};

#endif
