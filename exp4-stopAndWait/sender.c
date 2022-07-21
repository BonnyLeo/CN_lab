# include <stdio.h>
# include <netinet/in.h>
# include <arpa/inet.h>

void chat(int sockaddr){

}

int main(){

    struct sockaddr_in server_addr,client_address;
    int sockfd,clientfd,client_size;

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr('127.0.0.1');
    server_addr.sin_port = htons(8080);

    if ( bind(sockfd,(struct sockaddr *) &server_addr,sizeof(server_addr)) != -1)
        return (0);
    printf("binding successfull");

    if (listen(sockfd,1) == -1)
        return 0;

}