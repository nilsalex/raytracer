#ifndef TILED_PLANE_HPP
#define TILED_PLANE_HPP

#include "plane.hpp"

class TiledPlane : public Plane {
  private:
    Vector unit_1_;
    Vector unit_2_;
    Material* material_t_;

  public:
    TiledPlane(void);
    TiledPlane(Vector const& point, Vector const& normal);
    TiledPlane(TiledPlane const& plane);
    ~TiledPlane(void);

    void set_unit_1(Vector const& v);
    Vector get_unit_1(void) const;
    void set_unit_2(Vector const& v);
    Vector get_unit_2(void) const;
    void set_material_t(Material* material);
    Material* get_material_t(void) const;
    bool Hit(Ray &ray, double &t) const;
};

#endif
