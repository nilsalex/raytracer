#include "scene/parse.hpp"

char* Parse::ReadComment(int count, char *buffer) {
  char done = 0;
  while (1) {
    switch (*buffer++) {
      case '\n':
        done = 1;
        break;
      case '\r':
        done = 1;
        break;
      default:
        break;
    }
    count++;
    if (done == 1) {
      break;
    }
  }
  return buffer;
}

char* Parse::ReadDigits(int count, char *buffer, int ERROR_NUMBER, char *filename) {
  unsigned char done = 0, sign = 0, digit = 0;
  char temp_buf[1024];

  Digit.n = 0;
  while (1) {
    switch (*buffer) {
      case ' ':
        break;
      case '=':
        while (1) {
          count++;
          buffer++;
          switch(*buffer) {
            case ' ':
              if (digit > 0) {
                break;
              }
              digit = 0;
              break;
            case '-':
              if (sign > 0 || digit > 0) {
                done = 1;
                Digit.n = 0;
                break;
              }
              sign++;
              temp_buf[digit++] = *buffer;
              break;
            case '+':
              if (sign > 0 || digit > 0) {
                done = 1;
                Digit.n = 0;
                break;
              }
              sign++;
              temp_buf[digit++] = *buffer;
              break;
            case ';':
              temp_buf[digit] = '\0';
              Digit.v[Digit.n] = atof(temp_buf);
              Digit.n++;
              done = 1;
              digit = 0;
              break;
            case ',':
              if (Digit.n > 3) {
                fprintf(stdout, "\nScene::ReadDigits: [%s] More values than expected in file %s\n", temp_buf, filename);
                Digit.v[0] = Digit.v[1] = Digit.v[2] = 0;
                ERROR_NUMBER = 101;
                break;
              }
              temp_buf[digit] = '\0';
              Digit.v[Digit.n] = atof(temp_buf);
              Digit.n++;
              sign = 0;
              digit = 0;
              break;
            default:
              if (*buffer != '.' && !isdigit(*buffer)) {
                done = 1;
                Digit.n = 0;
              }
              temp_buf[digit++] = *buffer;
              break;
          }
          if (done == 1) {
            break;
          }
        }
        break;
      default:
        done = 1;
        break;
    }
    count++;
    buffer++;
    if (done==1) {
      break;
    }
  }
  if (Digit.n == 0) {
    fprintf(stdout, "\nScene::ReadDigits: [%s] Error reading digits in file %s\n", temp_buf, filename);
    Digit.v[0] = Digit.v[1] = Digit.v[2] = 0;
    ERROR_NUMBER = 101;
  }

  return buffer;
}
