#include <stdio.h>
#include "complex.h"

void complex_add(complex *z1, const complex *z2)
{
  z1->re += z2->re;
  z1->im += z2->im;
}

void complex_print(const complex *z)
{
  printf("%f + %f i", z->re, z->im);
}


/* Part 2: 2D Vectors over complex numbers. */
