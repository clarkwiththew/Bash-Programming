

#ifndef _solve_H
#define _solve_H

#include "line.h"

typedef struct {
double x , y;
} point ;

// Compute the smallest upright bounding box of the given array of points.
int solve ( point *p , const line *L1 , const line * L2 );

#endif




/* Part 3: main */
