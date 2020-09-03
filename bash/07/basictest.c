#include <stdio.h>
#include "point.h"

int main(void)
{
  point a[3] = { {3, 14}, {-5, 7}, {45, -34} };

  // Basic test of save_point_array.
  save_point_array("points-saved", 3, a);
  // Compare points1-saved with points-sample.

  // Basic test of load_point_array.
  point b[3] = { {0, 0}, {0, 0}, {0, 0} };
  int r;
  r = load_point_array("points-sample", 3, b);
  if (r != 3) {
    fprintf(stderr, "error when reading points-sample\n");
    return 1;
  }
  int i;
  for (i = 0; i < 3; i++) {
    if (b[i].x != a[i].x) {
      fprintf(stderr, "b[%d].x = %d is wrong\n", i, b[i].x);
    }
    if (b[i].y != a[i].y) {
      fprintf(stderr, "b[%d].y = %d is wrong\n", i, b[i].y);
    }
  }
  return 0;

  // When marking, a very different main with very different test cases will be
  // used for testing.
}
