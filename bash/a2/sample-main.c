#include <stdio.h>
#include "records.h"

int main(void)
{
  FILE *f = fopen("sample.dat", "r+");
  if (f == NULL) {
    perror("sample-main fopen");
    return 1;
  }

  // Get Dennis Ritchie YOB
  short y;
  if (get_yob(f, "Dennis Ritchie", &y)) {
    printf("Ritchie YOB=%hd\n", y);
  } else {
    printf("Ritchie not found\n");
  }

  // Add Tony Hoare's record.
 set_yob(f, "Charles Anthony Richard Hoare", 1934);
//  // https://en.wikipedia.org/wiki/Tony_Hoare
//  // also example of 29 characters name!
//
//  // Change Archimedes's YOB to the best estimate 288 BCE, hex fee0
 set_yob(f, "Archimedes", -288);

  fclose(f);
  return 0;
}
