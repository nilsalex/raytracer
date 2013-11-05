#ifndef RAY_HPP
#define RAY_HPP

#include "math/vector.hpp"
#include "material/material.hpp"

class HitInfo {
  public:
    Vector position;
    Vector normal;
    Material *material;
    double distance;

    HitInfo(void)
      : position(0.0, 0.0, 0.0),
        normal(0.0, 0.0, 0.0),
        material(),
        distance(0.0) {}

    ~HitInfo() {}
};

class Ray {
  private:
    Vector origin_;
    Vector direction_;

  public:
    Ray(void);
    Ray(Vector const& origin, Vector const& direction);
    Ray(Ray const& ray);
    ~Ray(void);

    HitInfo hit_info;
    Vector get_origin(void) const;
    void set_origin(Vector const& origin);
    Vector get_direction(void) const;
    void set_direction(Vector const& direction);

    Ray& operator= (Ray const& ray);
}; 

#endif
