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
#include <ctype.h>
const int READ =0, WRITE=1;

void up(char * holder) {
while (*holder) {
    *holder = toupper((unsigned char) *holder);
    holder++;
  }

}

int compareTwo(int a, int b){
    if (a>b)
    {return 1;}
    return 0;
}

void do_left(int fd_read, int fd_write)
{
    int sockval;

    int meslen = 512;
    char buf[meslen];
    int arrayCli[FD_SETSIZE];
    int numcli = FD_SETSIZE;

    dup2(fd_write, WRITE);
           close(fd_read);
           close(fd_write);
    dup2(fd_read, READ);
        close(fd_read);
        close(fd_write);

    for(;;)
    {
        fd_set filedirset;
        
        FD_ZERO(&filedirset);
        FD_SET(sockval, &filedirset);
        int arrvalmax = sockval;
        
        int j = 0;

        while (   j < numcli )
        {
            if (compareTwo(arrayCli[j],0)==1)
            {
                FD_SET( arrayCli[j] , &filedirset);
                switch (compareTwo(arrayCli[j], arrvalmax))
                {
                    case 1:
                        arrvalmax = arrayCli[j];
                        break;
                }
            }
            j++;
        }
        struct sockaddr_in addrnum;

        int lengthadress = sizeof(addrnum);
        int  activity = select( arrvalmax + 1 , &filedirset , NULL , NULL , NULL);
        if (activity==-1){exit(1);}
        int acceptval;
        if (FD_ISSET(sockval, &filedirset))
        {
            acceptval = accept(sockval,(struct sockaddr *)&addrnum, (socklen_t*)&lengthadress);
            if ((acceptval)==-1)
            {
                exit(1);

            }

            addSock(numcli,arrayCli,acceptval );
        }
        int i=0;
        while (i < numcli)
        {
            int sockdir;
            sockdir = arrayCli[i];
            if (FD_ISSET( sockdir , &filedirset))
            {
                
                int readint;
                if ((readint = read( sockdir , buf, buf-1)) == 0)
                {
                    
                    close( sockdir );
                    arrayCli[i] = 0;
                    if (readint==0) {exit(0);}

                }
                else
                {
                    up(buf);
                        write(sockdir , buf , strlen(buf) );
                    
                }
                                
            }
            i++;
        }
        
    }
}
