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
void transfer (int socket_fd){

    int frame_no=0,frame_mod2=0,prev_frame_mod2,skip=0,expected=0;
    printf("\nSend\tFrame status\tACK status\n");

    while (read(socket_fd,&frame_mod2,sizeof(frame_mod2)) != 0){
        printf("\n%d\t Frame no:%d\t", frame_no, frame_mod2);
        skip++;

        if(skip ==6){
            
            continue;
        }

        if(expected == frame_mod2){
            frame_mod2 = (frame_mod2+1)%2;
            expected = frame_mod2;

            printf("ACK no:%d", frame_mod2);
            write(socket_fd,&frame_mod2,sizeof(frame_mod2));
            frame_no++;
        }
        else
            printf("Wrong frame");
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