#ifndef IMAGE_HPP
#define IMAGE_HPP

class Image {
  public:
    virtual ~Image(void) {};
//    virtual void Read(char const *filename) const = 0;
    virtual void Write(char const* filename) const = 0;
    virtual void set_colour(int const& r, int const& g, int const& b) = 0;
};

#endif
