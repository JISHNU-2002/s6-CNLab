#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define max 1024

void send_file(int sock){
    char buf[max];
    FILE *fp;
    char *filename = "client_file.txt";
    fp = fopen(filename,"r");

    if(fp == NULL){
        printf("[-]error in file operation\n");
        exit(0); 
    }

    while(fgets(buf,max,fp) != NULL){
        int n = send(sock,buf,max,0);
        if(n < 0){
            printf("[-]error in sending file\n");
            exit(0);
        }
        printf("[+]sending data : %s",buf);     
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
    }
    printf("[+]TCP socket created\n");
    
    server.sin_family = AF_INET;
    server.sin_port = 8000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int n = sizeof(server);
    int c_sock = connect(s_sock,(struct sockaddr*)&server,n);
    if(c_sock < 0){
        printf("[-]client not connected\n");
        exit(0);
    }
    printf("[+]client connected\n\n");

    send_file(s_sock);  
    printf("\n\n[+]file transfer success\n");

    printf("[-]client disconnected\n");
    close(s_sock);
    return 0;
}
