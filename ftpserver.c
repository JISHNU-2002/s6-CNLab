#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define max 1024

void receive_file(int sock){
    char buf[max];
    FILE *fp;
    fp = fopen("server_file.txt","w");
    
    if(fp == NULL){
        printf("[-]error in file operation\n");
        exit(0);
    }
    
    while(1){
        int n = recv(sock,buf,max,0);
        if(n <= 0){
            printf("\n[-]end of file\n");
            break;
        }
        printf("[+]receiving data : %s",buf);
        fprintf(fp,"%s",buf);
        bzero(buf,max);
    }
    return;
}
int main(){
    struct sockaddr_in server,client;
    int s_sock = socket(AF_INET,SOCK_STREAM,0);
    if(s_sock < 0){
        printf("[-]TCP socket error\n");
        exit(0);
    }else{
        printf("[+]TCP socket created\n");
    }
    server.sin_family = AF_INET;
    server.sin_port = 8000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int b = bind(s_sock,(struct sockaddr*)&server,sizeof(server));
    if(b < 0){
        printf("[-]bind error\n");
        exit(0);
    }else{
        printf("[+]bind success\n");
    }
    
    int l = listen(s_sock,10);
    if(l < 0){
        printf("[-]server not listening\n");
        exit(0);
    }else{
        printf("[+]server listening\n");
    }

    int n = sizeof(client);
    int c_sock = accept(s_sock,(struct sockaddr*)&client,&n);
    if(c_sock < 0){
        printf("[-]client not accepted\n");
        exit(0);
    }else{
        printf("[+]client accepted\n\n");
    }
    
    receive_file(c_sock);
    printf("\n[+]file transfer complete\n");

    printf("[-]client disconnected\n");
    close(c_sock);
    close(s_sock);
    return 0;
}
