#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define max 1024

int main(){
    struct sockaddr_in server,client;
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0){
        printf("[-]TCP socket error\n");
        exit(0);
    }else{
        printf("[+]TCP socket created\n");
    }

    server.sin_family = AF_INET;
    server.sin_port = 8000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int n = sizeof(server);
    int c_sock = connect(sockfd,(struct sockaddr*)&server,n);
    if(c_sock < 0){
        printf("[-]client not connected\n");
        exit(0);
    }else{
        printf("[+]client connected\n\n");
    }

    char buf[max];
    FILE *fp;
    fp = fopen("client_file.txt","r");

    if(fp == NULL){
        printf("[-]error in file operation\n");
        exit(0); 
    }

    while(fgets(buf,max,fp) != NULL){
        send(sockfd,buf,max,0);
        printf("[+]sending data : %s",buf);     
        bzero(buf,max);
    } 
    printf("\n\n[+]file transfer success\n");

    printf("[-]client disconnected\n");
    close(sockfd);
    return 0;
}
