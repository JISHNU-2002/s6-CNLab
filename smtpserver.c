#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(){
    int server_sock,client_sock;
    struct sockaddr_in server,client;
    server_sock = socket(AF_INET,SOCK_STREAM,0);
    if(server_sock < 0){
        printf("[-]TCP server socket error\n");
        exit(0);
    }else{
        printf("[+]TCP socket created\n");
    }
    server.sin_family = AF_INET;
    server.sin_port = 4000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int b = bind(server_sock,(struct sockaddr*)&server,sizeof(server));
    if(b < 0){
        printf("[-]bind error\n");
        exit(0);
    }else{
        printf("[+]bind success\n");
    }

    listen(server_sock,1);
    printf("[+]server listening\n");

    int n = sizeof(client);
    client_sock = accept(server_sock,(struct sockaddr*)&client,&n);
    if(client_sock < 0){
        printf("[-]client connection not accepted\n");
        exit(0);
    }else{
        printf("[+]client connection accepted\n");
    }

    printf("\nSMTP - application layer protocol through TCP port 25\n\n");

    char buf[1024];
    bzero(buf,sizeof(buf));
    recv(client_sock,buf,sizeof(buf),0);
    if((strncmp(buf,"MAIL FROM",9))){
        printf("MAIL FROM expected\n");
        bzero(buf,sizeof(buf));
        strcpy(buf,"404");
        send(client_sock,buf,sizeof(buf),0);
    }else{
        printf("%s\n",buf);
        bzero(buf,sizeof(buf));
        strcpy(buf,"200");
        send(client_sock,buf,sizeof(buf),0);
    }

    bzero(buf,sizeof(buf));
    recv(client_sock,buf,sizeof(buf),0);
    if((strncmp(buf,"MAIL TO",7))){
        printf("MAIL TO expected\n");
        bzero(buf,sizeof(buf));
        strcpy(buf,"404");
        send(client_sock,buf,sizeof(buf),0);
    }else{
        printf("%s\n",buf);
        bzero(buf,sizeof(buf));
        strcpy(buf,"200");
        send(client_sock,buf,sizeof(buf),0);
    }

    bzero(buf,sizeof(buf));
    recv(client_sock,buf,sizeof(buf),0);
    if((strncmp(buf,"MAIL BODY",9))){
        printf("MAIL BODY expected\n");
        bzero(buf,sizeof(buf));
        strcpy(buf,"404");
        send(client_sock,buf,sizeof(buf),0);
    }else{
        printf("%s\n",buf);
        bzero(buf,sizeof(buf));
        strcpy(buf,"200");
        send(client_sock,buf,sizeof(buf),0);
    }

    bzero(buf,sizeof(buf));
    recv(client_sock,buf,sizeof(buf),0);
    if(strncmp(buf,"client",6)){
        printf("server : END\n");
    }else{
        printf("%s\n",buf);
        exit(0);
    }

    close(client_sock);
    close(server_sock);
    return 0;
}