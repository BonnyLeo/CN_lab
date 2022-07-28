# include <stdio.h>
# include <string.h>        // has memset()
# include <sys/socket.h>    // has socket()...
# include <arpa/inet.h>     // has inet_addr()
# include <netinet/in.h>    // has struct sockaddr
# include <stdlib.h>        // has exit()
# include <unistd.h>        // has close()
# include <sys/time.h>

# define PORT 8080

// function to chat
#define PORT 8080
void transfer(int sock)
{
int *n, i, e = 0, c = 0, k = 0;
n = &i;
while (read(sock, n, sizeof(i)) != 0)
{
if (e == i)
{
printf("\nFrame %d received\t", e);
e++;
i++;
write(sock, n, sizeof(i));
printf("\nAck %d\n", i);
}
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
    
    transfer(socket_fd);

    close(socket_fd);

    return 0;
}