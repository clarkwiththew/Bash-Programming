
#ifndef _VECTOR_H
#define _VECTOR_H

#include "complex.h"

typedef struct vector
{
  complex x1, x2;
} vector;

// Compute the smallest upright bounding box of the given array of points.
void vector_add(vector *v1, const vector *v2);

void vector_print(const vector *v);

#endif




/* Part 3: main */
