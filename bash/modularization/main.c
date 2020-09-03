#include <stdio.h>

#include "complex.h"

#include "vector.h"

/* Part 3: main */

int main(void)
{
  vector v1, v2;

  v1.x1.re = 3;
  v1.x1.im = -2;
  v1.x2.re = 1;
  v1.x2.im = 0;
  v2.x1.re = 1;
  v2.x1.im = 2;
  v2.x2.re = -1;
  v2.x2.im = 4;
  vector_add(&v1, &v2);
  vector_print(&v1);
  printf("\n");
  return 0;
}
