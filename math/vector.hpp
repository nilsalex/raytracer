#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector {
  private:
    double x_, y_, z_;

  public:
    Vector(void);
    Vector(Vector const& other);
    Vector(double const& x, double const& y_, double const& z_);
    ~Vector(void);

    double get_x(void) const;
    double get_y(void) const;
    double get_z(void) const;

    void set_x(double const& x);
    void set_y(double const& y);
    void set_z(double const& z);

    Vector & operator= (Vector const& v);
    Vector operator+ (Vector const& v) const;
    Vector operator- (Vector const& v) const;
    Vector operator* (double const& d) const;
    Vector operator/ (double const& d) const;
    double operator* (Vector const& v) const;

    Vector Cross(Vector const& v) const;
    double Length(void) const;
    void Normalize(void);
};

#endif
