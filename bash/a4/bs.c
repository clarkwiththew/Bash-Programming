////Example code: A simple server side code, which echos back the received message.
////Handle multiple socket connections with select and fd_set on Linux
//#include <stdio.h>
//#include <string.h> //strlen
//#include <stdlib.h>
//#include <errno.h>
//#include <unistd.h> //close
//#include <arpa/inet.h> //close
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
//
//#define TRUE 1
//#define FALSE 0
//#define PORT 8888
//
//int main(int argc , char *argv[])
//{
//    int opt = TRUE;
//    int master_socket , addrlen , new_socket , client_socket[30] ,
//        max_clients = 30 , activity, i , valread , sd;
//    int max_sd;
//    struct sockaddr_in address;
//
//    char buffer[1025]; //data buffer of 1K
//
//    //set of socket descriptors
//    fd_set readfds;
//
//    //a message
//    char *message = "ECHO Daemon v1.0 \r\n";
//
//    //initialise all client_socket[] to 0 so not checked
//    for (i = 0; i < max_clients; i++)
//    {
//        client_socket[i] = 0;
//    }
//
//    //create a master socket
//    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
//    {
//        perror("socket failed");
//        exit(EXIT_FAILURE);
//    }
//
//    //set master socket to allow multiple connections ,
//    //this is just a good habit, it will work without this
//    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
//        sizeof(opt)) < 0 )
//    {
//        perror("setsockopt");
//        exit(EXIT_FAILURE);
//    }
//
//    //type of socket created
//    address.sin_family = AF_INET;
//    address.sin_addr.s_addr = INADDR_ANY;
//    address.sin_port = htons( PORT );
//
//    //bind the socket to localhost port 8888
//    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
//    {
//        perror("bind failed");
//        exit(EXIT_FAILURE);
//    }
//    printf("Listener on port %d \n", PORT);
//
//    //try to specify maximum of 3 pending connections for the master socket
//    if (listen(master_socket, 3) < 0)
//    {
//        perror("listen");
//        exit(EXIT_FAILURE);
//    }
//
//    //accept the incoming connection
//    addrlen = sizeof(address);
//    puts("Waiting for connections ...");
//
//    while(TRUE)
//    {
//        //clear the socket set
//        FD_ZERO(&readfds);
//
//        //add master socket to set
//        FD_SET(master_socket, &readfds);
//        max_sd = master_socket;
//
//        //add child sockets to set
//        for ( i = 0 ; i < max_clients ; i++)
//        {
//            //socket descriptor
//            sd = client_socket[i];
//
//            //if valid socket descriptor then add to read list
//            if(sd > 0)
//                FD_SET( sd , &readfds);
//
//            //highest file descriptor number, need it for the select function
//            if(sd > max_sd)
//                max_sd = sd;
//        }
//
//        //wait for an activity on one of the sockets , timeout is NULL ,
//        //so wait indefinitely
//        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
//
//        if ((activity < 0) && (errno!=EINTR))
//        {
//            printf("select error");
//        }
//
//        //If something happened on the master socket ,
//        //then its an incoming connection
//        if (FD_ISSET(master_socket, &readfds))
//        {
//            if ((new_socket = accept(master_socket,
//                    (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
//            {
//                perror("accept");
//                exit(EXIT_FAILURE);
//            }
//
//            //inform user of socket number - used in send and receive commands
////            printf("New connection , socket fd is %d , ip is : %s , port : %d
////                \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs
////                (address.sin_port));
////
//            //send new connection greeting message
//            if( send(new_socket, message, strlen(message), 0) != strlen(message) )
//            {
//                perror("send");
//            }
//
//            puts("Welcome message sent successfully");
//
//            //add new socket to array of sockets
//            for (i = 0; i < max_clients; i++)
//            {
//                //if position is empty
//                if( client_socket[i] == 0 )
//                {
//                    client_socket[i] = new_socket;
//                    printf("Adding to list of sockets as %d\n" , i);
//
//                    break;
//                }
//            }
//        }
//
//        //else its some IO operation on some other socket
//        for (i = 0; i < max_clients; i++)
//        {
//            sd = client_socket[i];
//
//            if (FD_ISSET( sd , &readfds))
//            {
//                //Check if it was for closing , and also read the
//                //incoming message
//                if ((valread = read( sd , buffer, 1024)) == 0)
//                {
//                    //Somebody disconnected , get his details and print
//                    getpeername(sd , (struct sockaddr*)&address , \
//                        (socklen_t*)&addrlen);
//                    printf("Host disconnected , ip %s , port %d \n" ,
//                        inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
//
//                    //Close the socket and mark as 0 in list for reuse
//                    close( sd );
//                    client_socket[i] = 0;
//                }
//
//                //Echo back the message that came in
//                else
//                {
//                    //set the string terminating NULL byte on the end
//                    //of the data read
//                    buffer[valread] = '\0';
//                    send(sd , buffer , strlen(buffer) , 0 );
//                }
//            }
//        }
//    }
//
//    return 0;
//}
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
int getmaxval(int arrlen, int arr[]){
int i=0;
       int currmax  = arr[0];
while ( i < arrlen  )
{
  // int socketarrval  = arr[i];
    //int currmax;
    if(currmax < arr[i])
    {currmax = arr[i];}
    i++;
}
    return currmax;
}

void setClients(int arrlen, int arr[],fd_set *filedir){
        int i=0;
    int socketaval;
        while ( i < arrlen  )
        {
            socketaval  = arr[i];
            if(socketaval > 0)
            { FD_SET( socketaval , filedir);}
            i++;
        }
}
void setzero(int arrlen, int arr[]){
    int j=0;
    while (j < arrlen)
    {
        arr[j] = 0;
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

int main(int argc , char *argv[])
{
    int port= atoi(argv[1]);
    int socketarrval;
    //int opt = 1;
    int sockfd[FD_SETSIZE];
    int maxnum = FD_SETSIZE ;
    setzero(maxnum,sockfd);

    int lengthMess = 76;
    char buf[lengthMess];
    char messHold[lengthMess];
    int socketmax;
    struct sockaddr_in addr;
    
    fd_set fildirread;
    char mess[80];
  //  int j=0;
//    while (j < maxnum)
//    {
//        sockfd[j] = 0;
//        j++;
//    }
    
    
    struct sigaction act;
    act.sa_handler = SIG_IGN;
    sigaction(SIGPIPE, &act, NULL);
    int serverSocket = socket(AF_INET , SOCK_STREAM , 0);
    
    if( serverSocket == 0)
    {
        exit(1);
    }
    

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons( port );
    int bindval=bind(serverSocket, (struct sockaddr *)&addr, sizeof(addr));
    if (bindval<0)
    {
        exit(1);
    }
    int listenval=listen(serverSocket, 5);
    if ( listenval< 0)
    {
        exit(1);
    }
    int addrval = sizeof(addr);
    for(;;)
    {
        FD_ZERO(&fildirread);
        FD_SET(serverSocket, &fildirread);
        int socketmax = serverSocket;
        setClients(maxnum,sockfd,&fildirread);

        socketmax=getmaxval(maxnum,sockfd);

        int selectval = select( socketmax + 1 , &fildirread , NULL , NULL , NULL);

        int fdval=FD_ISSET(serverSocket, &fildirread);
        if (fdval==1)
        {
            int acceptval = accept(serverSocket,(struct sockaddr *)&addr, (socklen_t*)&addrval);
            if (acceptval<0)
            {
                exit(1);
            }
            int sendval=send(acceptval, mess, strlen(mess), 0);
            //            if(sendval  != strlen(mess) )
            //            {
            //                perror("send");
            //            }
            
            //tag2
            addSock(maxnum,sockfd, acceptval );
//            int i=0;
//
//            while ( i < maxnum)
//            {
//                if( sockfd[i] == 0 )
//                {
//                    sockfd[i] = acceptval;
//                    break;
//                }
//                i++;
//            }
        }
        int i=0;
        while (i < maxnum)
        {
            socketarrval = sockfd[i];
            int fdisval=FD_ISSET( socketarrval , &fildirread);
            if (fdisval==1)
            {
                int readint = read( socketarrval , buf, lengthMess-1);
                switch ( readint)
                {
                    case 0:
                    sockfd[i] = 0;

                    close( socketarrval );
                    
                
                
                    default:
                    if(strncmp(buf,"!",1)==0)
                    {//clean up mesage depot array
                        messHold[readint] = '\0';
                        strcpy(messHold, buf+1);
                    }
                    if(strcmp(buf,"?\n")==0)
                    {
                        send(socketarrval , messHold , strlen(messHold) , 0 );
                    }
                }
                
                memset(buf, '\0', sizeof(buf) -1);
                
            }
            i++;
        }
        
    }
    return 0;
}

//when to close server?
//when to exit accept, select?
