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


void setzero(int arrlen, int arr[]){
    int j=0;
    while (j < arrlen)
    {
        arr[j] = 0;
        j++;
    }
}
void setnull(int arrlen, char arr[]){
    int j=0;
    while (j < arrlen)
    {
        arr[j] = '\0';
        j++;
    }
}

void addSock(int arrlen, int arr[], int toadd){
    int i=0;
    while ( i < arrlen)
    {
        if( arr[i] == 0 )
        {
            arr[i] = toadd;
            break;
        }
        i++;
    }
}
int compareTwo(int a, int b){
    if (a>b)
    {return 1;}
    return 0;
}

int main(int argc , char *argv[])
{
    //int portnum= 54329;
    int portnum= atoi(argv[1]);
    if (portnum<1024||portnum>65535){exit(1);}
    
    int meslen = 76;
    char buf[meslen];
    char toSend[meslen];
    setnull(meslen,toSend);
    
    int arrayCli[FD_SETSIZE];
    int numcli = FD_SETSIZE;
    setzero(numcli,arrayCli);
    
    struct sigaction act;
    act.sa_handler = SIG_IGN;
    sigaction(SIGPIPE, &act, NULL);
    int sockval;
    
    if( ( sockval = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    {
        exit(1);
        
    }
    struct sockaddr_in addrnum;
    
    addrnum.sin_family = AF_INET;
    addrnum.sin_addr.s_addr = INADDR_ANY;
    addrnum.sin_port = htons( portnum );
    
    if (bind(sockval, (struct sockaddr *)&addrnum, sizeof(addrnum))==-1)
    {
        exit(1);
    }
    if (listen(sockval, 5) ==-1)
    {
        exit(1);
    }
    int lengthadress = sizeof(addrnum);
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
                if ((readint = read( sockdir , buf, meslen-1)) == 0)
                {
                    
                    close( sockdir );
                    arrayCli[i] = 0;
                    
                }
                else
                {
                    
                    int bytestr=sizeof(buf)-1;
                    if(strncmp(buf,"!",1)==0&&bytestr<=76)
                    {
                        
                        if(strchr(buf, '\n') != NULL){
                            memset(toSend, '\0', sizeof(toSend)-1);
                            toSend[readint] = '\0';
                            strcpy(toSend, buf+1);
                            int end_position=strlen(toSend);
                            toSend[end_position] = '\0';
                            
                        }
                        
                        if(buf[1]=='\n'){
                            toSend[0]='\n';
                            toSend[1]='\0';
                        }
                        else if(buf[2]=='\n'){
                            toSend[0]=buf[1];
                            toSend[1]='\n';
                            toSend[2]='\0';
                        }
                        else if(buf[3]=='\n'){
                            toSend[0]=buf[1];
                            toSend[1]=buf[2];
                            toSend[2]='\n';
                            toSend[3]='\0';
                        }
                        
                    }
                    else if(strcmp(buf,"?\n")==0)
                    {
                        send(sockdir , toSend , strlen(toSend) , 0 );
                    }
                }
                
                memset(buf, '\0', sizeof(buf)-1);
                
            }
            i++;
        }
        
    }
    return 0;
}

