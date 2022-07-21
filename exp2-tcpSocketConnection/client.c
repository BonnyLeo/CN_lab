# include <stdio.h>
# include <string.h>        // has memset()
# include <sys/socket.h>    // has socket()...
# include <arpa/inet.h>     // has inet_addr()
# include <netinet/in.h>    // has struct sockaddr
# include <stdlib.h>        // has exit()
# include <unistd.h>        // has close()

# define PORT 8080

// function to chat
void chat (int socket_fd){
    while(1){
        char server_msg[1000],client_msg[1000];

        // clear buffers
        memset(server_msg,'\0',sizeof(server_msg));
        memset(client_msg,'\0',sizeof(client_msg));
        
        // Get message from user
        printf("enter message : ");
        scanf("%s",&client_msg);

        // Sending message 
        if(send(socket_fd,client_msg,sizeof(client_msg),0) < 0)
            printf("unable to send.\n");

        // Exiting condition
        if(strcmp(client_msg,"exit") == 0 ){
            printf("exiting program . . .");
            exit(0);
        }
        
        // Recieving message
        if(recv(socket_fd,server_msg,sizeof(server_msg),0) < 0)
            printf("error receiving server message.\n");
        
        printf("server message: %s\n",server_msg);

    }
}


int main(){
    int socket_fd;
    struct sockaddr_in server_addr;

    // create socket
    socket_fd = socket(AF_INET,SOCK_STREAM,0);

    if(socket_fd != -1)
        printf("socket creation successfull . . .\n");
    else {
        printf("socket creation failed...\n");
        exit(0);
    }
    
    // set port and IP the same as server-side
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr =inet_addr("127.0.0.1");
    server_addr.sin_port =htons(PORT);

    // send connection request to server
    if (connect(socket_fd,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0 ){
        printf("connection with the server failed...\n");
        exit(0);
    }else
        printf("connection successful.\n");
    
    chat(socket_fd);

    close(socket_fd);

    return 0;
}