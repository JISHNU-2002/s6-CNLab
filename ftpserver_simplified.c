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

    int b = bind(sockfd,(struct sockaddr*)&server,sizeof(server));
    if(b < 0){
        printf("[-]bind error\n");
        exit(0);
    }else{
        printf("[+]bind success\n");
    }
    
    int l = listen(sockfd,10);
    if(l < 0){
        printf("[-]server not listening\n");
        exit(0);
    }else{
        printf("[+]server listening\n");

    }
   
    int n = sizeof(client);
    int a = accept(sockfd,(struct sockaddr*)&client,&n);
    if(a < 0){
        printf("[-]client not accepted\n");
        exit(0);
    }else{
        printf("[+]client accepted\n\n");
    }

    char buf[max];
    FILE *fp;
    fp = fopen("server_file.txt","w");
    
    if(fp == NULL){
        printf("[-]error in file operation\n");
        exit(0);
    }
    
    while(1){
        int n = recv(a,buf,max,0);
        //printf("value of n = %d\n",n);
        if(n <= 0){
            printf("\n[-]end of file / file transfer completed\n");
            break;
        }
        printf("[+]receiving data : %s",buf);
        fprintf(fp,"%s",buf);
        bzero(buf,max);
    }
    printf("\n[+]file transfer complete\n");

    printf("[-]client disconnected\n");
    close(a);
    close(sockfd);
    return 0;
}
