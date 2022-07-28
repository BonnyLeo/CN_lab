# include <stdio.h>
# include <stdlib.h>        // has exit()
# include <string.h>        // has memset(),strcmp()
# include <sys/socket.h>    // has socket(),bind(),listen(),accept(),
# include <netinet/in.h>    // has structure sockaddr_in defined
# include <unistd.h>        // has close()
# include <arpa/inet.h>     // has inet_addr
# include <sys/time.h>      // for time

# define PORT 8080

// function to chat
void transfer (int socket_fd){
    
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    setsockopt(socket_fd,SOL_SOCKET,SO_RCVTIMEO,(const char *)&tv,sizeof(tv));
    printf("\nSend\tFrame status\tACK status\n");
    
    int frame_no,frame_mod2=0,prev_frame_mod2,skip=0;

    for(frame_no=0;frame_no<10;frame_no++){
        prev_frame_mod2 = frame_mod2;

        LABEL:
            skip++;
            frame_mod2 = frame_no % 2;
            write(socket_fd,&frame_mod2,sizeof(frame_mod2));
            printf("\n%d\t Frame no:%d\t", frame_no, frame_mod2);

            if (skip == 3){
                printf("ACK missing");
                goto LABEL;
            }

            if (read(socket_fd,&frame_mod2,sizeof(frame_mod2))){
                if (frame_mod2 == prev_frame_mod2){
                    printf("frame missing");
                    goto LABEL;

            }
            else
                printf("ACK no:%d", frame_mod2);
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