#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct player {
  char *name;
  unsigned hitpoints;
} player;

player *mk_player(const char *name)
{
  player *p;
    p=malloc(sizeof(player));
  p->hitpoints = 100;
   p->name = (char *) malloc(sizeof(char));
  strcpy(p->name, name);
  return p;
}

void free_player(player *p)
{
    free(p->name);
    free(p);
}

// Example usage. Nothing to fix inside.
int main(void)
{
  player *p1 = mk_player("Kungfu Buffertly");

  // now decrease hit points by 17,
  // and change first letter of the name
  p1->hitpoints -= 17;
  p1->name[0] = 'L';

  printf("%s has %d hit points\n", p1->name, p1->hitpoints);
  // Lungfu Buffertly has 83 hit points

  free_player(p1);

  return 0;
}
