#ifndef POINT_H
#define POINT_H

#include <stddef.h>
// for size_t

typedef struct point {
  int x, y;
} point;

size_t save_point_array(const char *pathname, size_t n, const point *a);

size_t load_point_array(const char *pathname, size_t n, point *a);

#endif  // #ifndef POINT_H
