#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

#define N 5     /* How many children to make. */
#define D 1200  /* Sleep 1200 seconds = 20 minutes */

int main(void)
{
  int i;
  pid_t p;

  for (i = 0; i < N; i++) {
    p = fork();
    if (p == 0) {
      close(0);
      close(1);
      close(2);
      if (i == 2) {
        //
          setsid();
      }
      sleep(D);
      return 0;
    }
  }
  return 0;
}

