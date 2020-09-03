/*
    C socket server example
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>    /* Internet domain header */
#include <arpa/inet.h>     /* only needed on my mac */
#include <sys/select.h>
/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>

int main(int argc , char *argv[])
{
    int portnum = atoi(argv[1]);

    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
    
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
{exit(1);}
    
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( portnum );
    
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
{exit(1);}
    //puts("bind done");
    
    //Listen
    int listval=listen(socket_desc , 3);
    if(listval==-1){exit(1);}
    //Accept and incoming connection
    //puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {exit(1);}

    //Receive a message from client
    
    
    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    {
        //Send the message back to client
    char line[80];
        //read(i, line, 76);

        //char start [2];
        int length=strlen(client_message);
        //sprintf(start,"%c",line[0]);


        if(strncmp(client_message,"!",1)==0){
            //new post
            char buf [76];
            strcpy(buf,client_message+1);
            //buf[length] = '\0';
            //strcpy(line,buf);
        }

        else if(strncmp(line,"?",1)==0){
           // int sendval=send(i, server_message,strlen(server_message),0);
           // if(sendval==-1){exit(1);}
        write(client_sock , client_message , strlen(client_message));
    }
    
    if(read_size == 0)
    {
        fflush(stdout);
    }
    else if(read_size == -1)
    {exit(1);}

    return 0;
}
}
