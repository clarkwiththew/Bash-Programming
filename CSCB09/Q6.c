#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
const int READ =0, WRITE=1;

void do_left(int fd_read, int fd_write)
{


}

void leftright(void)
{
  // parent begins

  int ltr[2];
  int rtl[2];

  pipe(ltr);
  pipe(rtl);

  pid_t left = fork();
  if (left == 0) {
    // left child code, part (a)
      do_left(rtl[READ],ltr[WRITE]);

  } else {
    pid_t right = fork();
    if (right == 0) {
      // right child code, part (b)
        close(fd_write);
      execlp("right", "right", (char*)NULL);
      exit(1);
    } else {
      close(fd_write);
      close(fd_read);
      wait(NULL);
      wait(NULL);
    }
  }
}
