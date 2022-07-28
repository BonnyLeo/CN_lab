# include <stdio.h>
# include <string.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <time.h>

# define PORT 8080

int chat(int socket_fd,struct sockaddr_in client_addr){

    int client_addr_len =sizeof(client_addr);
    char server_msg[1000],client_msg[1000];
    
    time_t t;
    time(&t);    
    char *a = ctime(&t);

    while(1){
        memset(server_msg,'\0',sizeof(server_msg));
        memset(client_msg,'\0',sizeof(client_msg));

        if (recvfrom(socket_fd,&client_msg,sizeof(client_msg),0,(struct sockaddr *)&client_addr,&client_addr_len) == -1){
            printf("error recieving message.");
        }
        printf("server message : %s\n",client_msg);

        printf("enter the msg : ");
        scanf("%s",&server_msg);

        if (sendto(socket_fd,server_msg,sizeof(server_msg),0,(struct sockaddr *)&client_addr,client_addr_len) == -1){
            printf("error recieving message.");
        }
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


    if (bind(socket_fd,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0){
        printf("binding failed\n");
        return -1;
    }
    printf("binding successfull\n");

    chat(socket_fd,client_addr);

    close(socket_fd);

}

