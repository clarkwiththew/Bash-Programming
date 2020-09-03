

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

    int child1=fork();
    if (child1==-1){
        return -1;
    }
    else if (child1==0){
        close(fd[1]);
        char path[1024]="/dev/fd/";
        char end [1024];
        sprintf(end,"%d",fd[0]);
        strcat(path ,end);
        int exec1 = execlp(prog1, prog1,path, NULL);
        if (exec1==-1){
            exit(37);
        }
    }

    else{
        int child2=fork();

        if (child2==-1){
            return -1;}

        else if (child2==0){
            int dupVal = dup2(fd[WRITE], WRITE);
            close(fd[READ]);
            close(fd[WRITE]);
            int exec2 = execvp(prog2, prog2_argv);
            if(exec2==-1){
                exit(37);
            }
            else {
            int statloc;
            close(fd[READ]);
            close(fd[WRITE]);
            pid_t wait2 = waitpid(child1,&statloc,0);
            status[1]=(statloc);//<---2nd parameter
            }
        }
        int statloc;
        pid_t wait1 = waitpid(child1,&statloc,0);
        status[0]=((statloc));//<---
    }

    return 0;

}

