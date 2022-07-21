# include <stdio.h>
# include <string.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>

# define PORT 8080

int chat(int socket_fd,struct sockaddr_in server_addr){

    int server_addr_len =sizeof(server_addr);
    char server_msg[1000],client_msg[1000];

    while(1){
        memset(server_msg,'\0',sizeof(server_msg));
        memset(client_msg,'\0',sizeof(client_msg));
        
        printf("enter the msg : ");
        scanf("%s",&client_msg);


        if (sendto(socket_fd,client_msg,sizeof(client_msg),0,(struct sockaddr *)&server_addr,server_addr_len) == -1){
            printf("error recieving message.");
        }

        if (recvfrom(socket_fd,&server_msg,sizeof(server_msg),0,(struct sockaddr *)&server_addr,&server_addr_len) == -1){
            printf("error recieving message.");
        }
        printf("server message : %s\n",server_msg);

    }
}

int main(){
    
    int socket_fd;
    struct sockaddr_in server_addr,client_addr;
    
    if ((socket_fd = socket(AF_INET,SOCK_DGRAM,0)) == -1){
        printf("socket creation failed.\n");
        return -1;
    }
    printf("socket creation successfull.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    chat(socket_fd,server_addr);

    close(socket_fd);

}

