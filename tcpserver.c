#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int server_sock,client_sock,b,n;
    struct sockaddr_in server,client;
    char buf[1024];

    server_sock = socket(AF_INET,SOCK_STREAM,0);
    if(server_sock < 0){
        printf("[-]TCP socket error\n");
        exit(0);
    }else{
        printf("[+]TCP socket created\n");
    }

    memset(&server,'\0',sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = 2000;
    server.sin_addr.s_addr = inet_addr("192.168.73.93");

    b = bind(server_sock,(struct sockaddr*)&server,sizeof(server));
    if(bind < 0){
        printf("[-]TCP bind error\n");
        exit(0);
    }else{
        printf("[+]TCP bind successfull\n");
    }

    listen(server_sock,1);
    printf("Server listening waiting for CLIENT...\n");
    n = sizeof(client);
    client_sock = accept(server_sock,(struct sockaddr*)&client,&n);
    if(client_sock < 0){
        printf("[-]Client connection error\n");
        exit(0);
    }else{
        printf("[+]Client connection accepted\n");
    }

    for(;;){
        recv(client_sock,buf,sizeof(buf),0);
        if(strcmp(buf,"end")==0){
            break;
        }
        printf("\nclient : %s",buf);
        printf("\nserver : ");
        gets(buf);
        send(client_sock,buf,sizeof(buf),0);
        if(strcmp(buf,"end")==0){
            break;
        }
    }
    close(client_sock);
    printf("[-]Client disconnected...\n");
    close(server_sock);
    return 0;
}