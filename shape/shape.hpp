#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "def.hpp"
#include "math/ray.hpp"
#include "material/material.hpp"
//#include "path/path.h"

#define SHAPE_EPSILON 0.1

class Shape {
  private:
    Material *material_;
//  Path *path_;
//  PathData *path_data_;
//  bool has_path_;
//  bool has_path_data_;
    double angle_;

  public:
    Shape(void);
    Shape(Shape const& shape);
    virtual ~Shape(void);

    void set_material(Material* material);
    Material* get_material(void) const;

//  void set_path(path const* path);
//  Path* get_path(void) const;
//  void set_path_data(PathData const* path_data);
//  PathData* get_path_data(void) const;
    void set_start_angle(double const& angle);
    double get_start_angle(void) const;
//  bool HasPath(void) const;
//  bool HasPathData(void) const;

    virtual void set_position(double const& X, double const& Y, double const& Z) = 0;
    virtual Vector get_position(void) const = 0;
    virtual bool Hit(Ray &ray, double &t) const = 0;
};

#endif
