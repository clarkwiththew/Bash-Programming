#include <stdio.h>

int substitute_function(const char *prog1, const char *prog2, char *prog2_argv[], int status[]);

int main(void)
{
  int status[2];
  char *args[] = { "sort", "-r", "test.txt", NULL };

  // like "uniq <(sort -r violinists.txt)"
  substitute_function("uniq", "sort", args, status);
  printf("exit statuses: %x %x\n", status[0], status[1]);

  return 0;
}
//H
//G
//C
//B
//A

