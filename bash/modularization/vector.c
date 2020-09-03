#include <stdio.h>
#include "vector.h"
#include "complex.h"

void vector_add(vector *v1, const vector *v2)
{
  complex_add(&v1->x1, &v2->x1);
  complex_add(&v1->x2, &v2->x2);
}

void vector_print(const vector *v)
{
  printf("(");
  complex_print(&v->x1);
  printf(", ");
  complex_print(&v->x2);
  printf(")");
}
