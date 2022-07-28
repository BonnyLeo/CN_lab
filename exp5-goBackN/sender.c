# include <stdio.h>
# include <stdlib.h>        // has exit()
# include <string.h>        // has memset(),strcmp()
# include <sys/socket.h>    // has socket(),bind(),listen(),accept(),
# include <netinet/in.h>    // has structure sockaddr_in defined
# include <unistd.h>        // has close()
# include <arpa/inet.h>     // has inet_addr
# include <time.h>      // for time


# define PORT 8080

// function to chat
void transfer (int socket_fd){
    struct timeval tv;
    tv.tv_sec=1;
    tv.tv_usec=0;
    srand(time(NULL));
    setsockopt(socket_fd,SOL_SOCKET,SO_RCVBUF,&tv,sizeof(tv));

    int frame_no,frame_no_mod4,head=0,tail=0,ack=-1;

    for (frame_no=0;frame_no<10;frame_no++){

        if( (tail-head)> 4 || frame_no==9){
            printf("\nTimeout resend from %d\n\n", head);
            head = tail;
            frame_no = head;
        }
        int flag = rand() % 2;
        printf("Frame %d send\n", tail);
        if (flag)
        write(socket_fd,&tail,sizeof(tail));
        tail++;        

        read(socket_fd,&ack,sizeof(ack));

        if(ack != -1){
            head++;
            printf("ACK %d\n", ack);
        }
    }
    

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

transfer(client_fd);

close(client_fd);
close(socket_fd);

return 0;
}