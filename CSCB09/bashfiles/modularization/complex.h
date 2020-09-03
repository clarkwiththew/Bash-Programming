#ifndef _COMPLEX_H
#define _COMPLEX_H

typedef struct complex
{
  double re, im;
} complex;

void complex_add(complex *z1, const complex *z2);

void complex_print(const complex *z);
#endif 


/* Part 2: 2D Vectors over complex numbers. */
