#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>
#include<fcntl.h>

int main(){
    int s_sock,c_sock;
    struct sockaddr_in server,client;
    s_sock = socket(AF_INET,SOCK_STREAM,0);
    if(s_sock < 0){
        printf("[-]error\n");
        exit(0);
    }else{
        printf("[+]\n");
    }
    server.sin_family = AF_INET;
    server.sin_port = 7000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("[+]client ready\n");
    
    int n = sizeof(server);
    c_sock = connect(s_sock,(struct sockaddr*)&server,n);
    if(c_sock < 0){
        printf("[-]client not conncted\n");
        exit(0);
    }else{
        printf("[+]client connected\n");
    }  
    printf("[+]client with individual ack scheme\n");

    int i,flag1=0,flag2=0;
    char buf[50];

    for(i=0;i<=9;i++){
        flag1=1;
        bzero(buf,sizeof(buf));
        if(i==8 && flag2==1){
            printf("here\n");
            flag2=0;
            read(c_sock,buf,sizeof(buf));
        }
        if(buf[strlen(buf)-1] != i+'0'){
            printf("discarded as out of order\n");
            i--;
        }else{
            printf("server : %s\nack - %d sent to server\n",buf,i);
            bzero(buf,sizeof(buf));
            strcpy(buf,"send ack of : ");
            buf[strlen(buf)] = i+'0';
            buf[strlen(buf)] = '\0';
            write(c_sock,buf,sizeof(buf));
        }
    }
    close(c_sock);
    return 0;
}