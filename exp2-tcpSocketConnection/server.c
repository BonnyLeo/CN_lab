    # include <stdio.h>
# include <stdlib.h>        // has exit()
# include <string.h>
# include <sys/socket.h>    // has socket(),bind(),listen(),accept(),
# include <netinet/in.h>    // has structure sockaddr_in defined
# include <unistd.h>
# include <arpa/inet.h>     // has inet_addr

# define PORT 8080

// function to chat
int chat(int client_fd){
    while(1){
        char server_msg[1000],client_msg[1000];

        // clear buffers
        memset(server_msg,'\0',sizeof(server_msg));
        memset(client_msg,'\0',sizeof(client_msg));

        // Recieve client's message
        if(recv(client_fd,client_msg,sizeof(client_msg),0) < 0){
            printf("error reading client message\n");
            return -1;
        }

        // Exiting condition
        if (strcmp(client_msg,"exit") == 0 ){
            printf("Client requests exit.\nexiting . . .");
            exit(0);
        }
        printf("client message: %s\n",client_msg);

        // Get input from user
        printf("enter ur message: ");
        scanf("%s",&server_msg);

        // Send the msg to server
        if(send(client_fd,server_msg,sizeof(server_msg),0) < 0){
            printf("error while sending the message\n");
            return -1;
        }

    }
    return 0;
}

int main(){

int socket_fd, client_fd, client_size;
struct sockaddr_in server_addr, client_addr;

//create socket
socket_fd = socket(AF_INET,SOCK_STREAM,0);

// set port and IP
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
server_addr.sin_port   = htons(PORT);


// Bind to the set port and IP
if (bind(socket_fd,(struct sockaddr *)&server_addr,sizeof(server_addr)) != 1)
    printf("socket binding successful\n");
else{
    printf("socket binding failed\n");
    exit(0);
}

// Listen for clients
if (listen(socket_fd,1) != -1 )
        printf("listening . . .\n");
else{
    printf("listening failed\n");
    exit(0);
}

// Accepting connection
client_size = sizeof(client_addr);
client_fd = accept(socket_fd, (struct sockaddr*)&client_addr, &client_size);
if (client_fd  != -1 )
    printf("connection successful\n");
else{
    printf("connection failed   .   .   . \n");
    exit(0);
}

chat(client_fd);

close(client_fd);
close(socket_fd);

return 0;
}