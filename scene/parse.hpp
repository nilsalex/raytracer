#ifndef PARSE_HPP
#define PARSE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

class Parse {
  public:
    struct digit {
      int n;
      double v[3];
    } Digit;

    Parse(void) {};
    ~Parse(void) {};

    char* ReadComment(int COUNT, char *buffer);
    char* ReadDigits(int COUNT, char *buffer, int ERROR_NUMBER, char *filename);
};

#endif
