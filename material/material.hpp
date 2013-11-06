#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "colour/rgb_colour.hpp"

class Material {
  private:
    double gloss_;
    double transparency_;
    double reflection_;
    double refraction_in_;
    double refraction_out_;
    RGBColour colour_;

  public:
    Material(void);
    virtual ~Material(void);

    double get_gloss(void) const;
    void set_gloss(double const& gloss);

    double get_transparency(void) const;
    void set_transparency(double const& transparency);

    double get_reflection(void) const;
    void set_reflection(double const& reflection);

    double get_refraction_in(void) const;
    void set_refraction_in(double const& refraction_in);
    double get_refraction_out(void) const;
    void set_refraction_out(double const& refraction_out);

    virtual bool HasTexture(void) const;

    virtual RGBColour get_colour(void) const;
    virtual void set_colour(RGBColour const& colour);
};

#endif
