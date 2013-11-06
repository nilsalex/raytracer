#ifndef TGA_HPP
#define TGA_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image/image.hpp"

class TGA : public Image {
  private:
    struct Colour {
      int red, green, blue;
    };
    Colour *colour_;
    int bitmap_, type_, rows_, cols_, count_;
    int getline_(FILE *file, char line[]) const;

  public:
    TGA(int const& bitmap, int const& type, int const& rowsp, int const& colsp, int const& count = 0);
    ~TGA(void);
//    void Read(char const* filename) const;
    void Write(char const* filename) const;
    void set_colour(int const& r, int const& g, int const& b);
};

#endif
