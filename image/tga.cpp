#include "image/tga.hpp"

TGA::TGA(int const& bitmap, int const& type, int const& rows, int const& cols, int const& count)
  : colour_(new Colour[rows * cols]),
    bitmap_(bitmap), type_(type), rows_(rows), cols_(cols), count_(count) {}

TGA::~TGA(void) {
  delete colour_;
}

//void TGA::Read(char const* filename) const {
//  fprintf(stdout, "TGA::Read: Not yet implemented\n");
//}

void TGA::Write(char const* filename) const {
  FILE *file = fopen(filename, "wb");

  if (file == NULL) {
    fprintf(stderr, "Can't open the file %s\n", filename);
  }

  fprintf(file, "%c%c", 0, 0); // Space for TGA header
  fprintf(file, "%c", type_); // Type of file format
  fprintf(file, "%c%c%c%c%c", 0, 0, 0, 0, 0); // Colour map specification = 0
  fprintf(file, "%c%c", 0, 0); // Origin X
  fprintf(file, "%c%c", 0, 0); // Origin Y
  fprintf(file, "%c%c", rows_&0x00FF, (rows_ & 0xFF00) / 256); // Number of rows
  fprintf(file, "%c%c", cols_&0x00FF, (cols_ & 0xFF00) / 256); // Number of cols
  fprintf(file, "%c", bitmap_); // Bitmap / Depth
  fprintf(file, "%c", 0); // Image descriptor byte - origin in lower left corner
  for (int c = 0; c < rows_ * cols_; c++) {
    fprintf(file, "%c%c%c", colour_[c].blue, colour_[c].green, colour_[c].red);
  }
  fclose(file);
}

void TGA::set_colour(int const& r, int const& g, int const& b) {
  if (count_ < rows_*cols_) {
    colour_[count_].red = r;
    colour_[count_].green = g;
    colour_[count_].blue = b;
    count_++;
  } else {
    fprintf(stderr, "Error writing colours: count_: %7d 3*rows_*cols_: %7d\n", count_, rows_*cols_);
  }
}

int TGA::getline_(FILE* file, char line[]) const {
  int i = 0;
  while (1) {
    line[i] = getc(file);
    if (line[i] == '\n' || line[i] == EOF) {
      break;
    }
    i++;
  }
  line[i] = '\0';
  return i;
}
