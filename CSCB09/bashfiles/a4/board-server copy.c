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

int main() {
    //    // create socket
    //    int listen_soc = socket(AF_INET, SOCK_STREAM, 0);
    //    if (listen_soc == -1) {
    //        perror("server: socket");
    //        exit(1);
    //    }
    //
    //
    //    //initialize server address
    //    struct sockaddr_in server;
    //    server.sin_family = AF_INET;
    //    server.sin_port = htons(1234);
    //    memset(&server.sin_zero, 0, 8);
    //    server.sin_addr.s_addr = INADDR_ANY;
    //
    //    // bind socket to an address
    //    if (bind(listen_soc, (struct sockaddr *) &server, sizeof(struct sockaddr_in)) == -1) {
    //      perror("server: bind");
    //      close(listen_soc);
    //      exit(1);
    //    }
    //
    //
    //    // Set up a queue in the kernel to hold pending connections.
    //    if (listen(listen_soc, 5) < 0) {
    //        // listen failed
    //        perror("listen");
    //        exit(1);
    //    }
    //
    //    struct sockaddr_in client_addr;
    //    unsigned int client_len = sizeof(struct sockaddr_in);
    //    client_addr.sin_family = AF_INET;
    //
    //    int client_socket = accept(listen_soc, (struct sockaddr *)&client_addr, &client_len);
    //    if (client_socket == -1) {
    //        perror("accept");
    //        return -1;
    //    }
    //
    //
    //    write(client_socket, "hello\r\n", 7);
    //
    //    char line[10];
    //    read(client_socket, line, 10);
    //    /* before we can use line in a printf statement, ensure it is a string */
    //    line[9] = '\0';
    //    printf("I read %s\n", line);
    
    
    
    
    //
    //    if (select(numfd, &read_fds, NULL, NULL, NULL) == -1) {
    //        perror("select");
    //        exit(1);
    //    }
    //  int select(int nfds, fd_set *readfds, fd_set *writefds,
    // fd_set *exceptfds, struct timeval *timeout);
    
    char server_message[256]="\n";
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket==-1){exit(1);}
    
    
    
    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(1234);
    server_address.sin_addr.s_addr=INADDR_ANY;
    
    
    int bindVal=bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    
    if(bindVal==-1){exit(1);}
    int listval=listen(server_socket, 5);
    int client_socket;
    client_socket=accept(server_socket, NULL, NULL);
    if(client_socket==-1){exit(1);}
    
    char line[10];
    read(client_socket, line, 76);
    //if read does not have newline, ignore


    
    char start [1024];
    int length=strlen(line);
    sprintf(start,"%c",line[0]);

    
    if(strcmp(start,"!")==0){
        //new post
        char buf [76];
        strncpy(buf,line+1,length);
        buf[length] = '\0';
        strcpy(server_message,buf);
    }
    
    else if(strcmp(start,"?")==0){
        int sendval=send(client_socket, server_message,sizeof(server_message),0);
        if(sendval==-1){exit(1);}
        
    }
    else{
        //ignore
        
    }
    
    

    
    
    //Clients can close connections just when the server sends replies. By default this kills the server. You must not let this happen.
    
    
    //if (client close) { server close}
    return 0;
}

//Example code: A simple server side code, which echos back the received message.
//Handle multiple socket connections with select and fd_set on Linux
#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> //close
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#define TRUE 1
#define FALSE 0
#define PORT 43210
int main(int argc , char *argv[])
{    int flagCount=0;

    int opt = TRUE;
    int master_socket , addrlen , new_socket , client_socket[FD_SETSIZE] ,
    max_clients = FD_SETSIZE , activity, i , valread , sd;
    int max_sd;
    struct sockaddr_in address;
    int msg_len = 76;
    char buffer[msg_len];
    char msg_depot[msg_len];
    //set of socket descriptors
    fd_set readfds;
    //a message
    char *message = "ECHO Daemon v1.0 \r\n";
    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++)
    {
        client_socket[i] = 0;
    }
    //create a master socket
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    //set master socket to allow multiple connections ,
    //this is just a good habit, it will work without this
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                   sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    //bind the socket to localhost port 8888
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);
    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");
    while(TRUE)
    {
        //clear the socket set
        FD_ZERO(&readfds);
        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;
        //add child sockets to set
        for ( i = 0 ; i < max_clients ; i++)
        {
            //socket descriptor
            sd = client_socket[i];
            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);
            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }
        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
        if ((activity < 0) && (errno!=EINTR))
        {
            printf("select error");
        }
        //If something happened on the master socket ,
        //then its an incoming connection
        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket,
                                     (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs
                   (address.sin_port));
            flagCount++;
            //send new connection greeting message
            if( send(new_socket, message, strlen(message), 0) != strlen(message) )
            {
                perror("send");
            }
            puts("Welcome message sent successfully");
            //add new socket to array of sockets
            for (i = 0; i < max_clients; i++)
            {
                //if position is empty
                if( client_socket[i] == 0 )
                {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n" , new_socket);
                    break;
                }
            }
        }
        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++)
        {
            sd = client_socket[i];
            if (FD_ISSET( sd , &readfds))
            {
                //Check if it was for closing , and also read the
                //incoming message
                if ((valread = read( sd , buffer, msg_len-1)) == 0)
                {
                    //Somebody disconnected , get his details and print
                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                    printf("Host disconnected , ip %s , port %d \n" ,
                           inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                    //Close the socket and mark as 0 in list for reuse
                    close( sd );
                    client_socket[i] = 0;
                    flagCount--;
                    if (flagCount==0){
                        {exit(1);}
                    }
                }
                //Echo back the message that came in
                else
                {
                    //set the string terminating NULL byte on the end
                    //of the data read
                    
                    if(strncmp(buffer,"!",1)==0)
                    {
                        memset(msg_depot, '\0', sizeof(msg_depot) -1); //clean up mesage depot array
                        msg_depot[valread] = '\0';
                        strcpy(msg_depot, buffer+1); //copy buffer to depot
                    }
                    if(strcmp(buffer,"?\n")==0)
                    {
                        send(sd , msg_depot , strlen(msg_depot) , 0 );
                    }
                }
                
                memset(buffer, '\0', sizeof(buffer) -1); //clean up buffer array for next read
                
            }

        }

    }
    return 0;
}

