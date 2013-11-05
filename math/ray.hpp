#ifndef RAY_HPP
#define RAY_HPP

#include "math/vector.hpp"

class Ray {
  private:
    Vector origin_;
    Vector direction_;

  public:
    Ray(Vector const& origin, Vector const& direction);
    ~Ray(void);
    Vector Evaluate(double const& t) const;
}; 

#endif
