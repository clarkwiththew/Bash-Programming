#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

#define MSGSIZE 1000

int procsub(const char *prog1, const char *prog2, char *prog2_argv[], int status[]);

int main(void)
{
    int status[2];
    char *args[] = { "sort", "-r", "violinists.txt", NULL };
    
    // like "uniq <(sort -r violinists.txt)"
    procsub("uniq", "sort", args, status);
    //printf("exit statuses: %x %x\n", status[0], status[1]);
    
    return 0;
}


int procsub(const char *prog1, const char *prog2, char *prog2_argv[], int status[])
{
    //char inbuf[MSGSIZE];
    
    int p[2], i;
    
    pid_t c1_pid, c2_pid;
    if (pipe(p) < 0)
        return -1;
    //printf("% d\n", p[0]);
    //printf("% d\n", p[1]);
    
    c1_pid = fork();

    if (c1_pid == 0)
    {
        execlp(prog1, prog1, "/dev/fd/3", NULL); //wrong for 2nd param p[0]
    }
    else
    {
        c2_pid = fork();
        
        if (c2_pid == 0)
        {
            printf("hello c2: %d\n", getpid());
            dup2(p[1],1); // redirect stdout to the write end of the pipe
            execvp (prog2, prog2_argv);
        }
        else
        {
            printf("hello main: %d\n", getpid());
        }
        
    }
    
    
    /*
     
     write(p[1], "hello 1", MSGSIZE);
     write(p[1], "hello 2", MSGSIZE);
     write(p[1], "hello 3", MSGSIZE);
     
     for (i=0; i<3; i++)
     {
     read(p[0], inbuf, MSGSIZE);
     printf("% s\n", inbuf);
     }
     */
    
    return 0;
}


//https://tldp.org/LDP/lpg/node11.html
//https://indradhanush.github.io/blog/writing-a-unix-shell-part-2/
//https://www.unix.com/programming/9563-writing-c-code-who-sort-lp-2.html
