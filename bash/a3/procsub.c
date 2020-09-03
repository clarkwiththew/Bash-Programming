#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

const int READ =0, WRITE=1;

int procsub(const char *prog1, const char *prog2, char *prog2_argv[], int status[])
{
    int fd[2];
    int pipeVal = pipe(fd);
    if (pipeVal==-1){
        return -1;
    }

    int child2=fork();
    if (child2==-1){
        return -1;
    }

    else if (child2==0){
        int dupVal = dup2(fd[WRITE], WRITE);
        close(fd[READ]);
        close(fd[WRITE]);
        int exec2 = execvp(prog2, prog2_argv);
        if(exec2==-1){
            fprintf(stderr,"execvp fails");
            exit(37);
        }

    }

    else{
        int child1=fork();

        if (child1==-1) {
            return -1;
        }

        else if (child1==0){
            close(fd[WRITE]);
            int stacloc2;
            char path[1024]="/dev/fd/";
            char end [1024];
            sprintf(end,"%d",fd[0]);
            strcat(path ,end);
            int exec1 = execlp(prog1, prog1,path, NULL);
            if (exec1==-1){
                fprintf(stderr,"execlp fails");
                exit(37);
            }
        }
        else {
            close(fd[WRITE]);
            close(fd[READ]);

            int stacloc1, stacloc2;
            pid_t wait2 = waitpid(child2,&stacloc2,0);
            if (wait2 == -1) {
                fprintf(stderr,"child2 is having problems\n");
                exit(37);
            }
            pid_t wait1 = waitpid(child1,&stacloc1,0);
            if (wait1 == -1) {
                fprintf(stderr,"child1 is having problems\n");
                exit(37);
            }

            status[0]=stacloc1;
            status[1]=stacloc2;
        }

    }

    return 0;

}






