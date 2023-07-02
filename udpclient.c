#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(){
    int server_sock,client_sock,n,num,fact;
    char buf[1024];
    struct sockaddr_in server,client;

    server_sock = socket(AF_INET,SOCK_DGRAM,0);
    server.sin_family = AF_INET;
    server.sin_port = 4000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(server_sock < 0){
        printf("[-]UDP socket error\n");
        exit(0);
    }else{
        printf("[+]UDP socket created\n");
    }
    printf("[+]Client ready\n");
    n = sizeof(server);

    //only for messaging client-server
    for(;;){
        printf("\nclient : ");
        gets(buf);
        sendto(server_sock,buf,sizeof(buf),0,(struct sockaddr*)&server,n);
        if(strcmp(buf,"end")==0){
            break;
        }
        
        recvfrom(server_sock,buf,sizeof(buf),0,(struct sockaddr*)&server,&n);
        if(strcmp(buf,"end")==0){
            break;
        }
        printf("server : %s\n",buf);
    }

    //send a number to server , to calculate it's factorial
    printf("Enter number to find factorial = ");
    scanf("%d",&num);
    sendto(server_sock,&num,sizeof(num),0,(struct sockaddr*)&server,n);
    recvfrom(server_sock,&fact,sizeof(fact),0,(struct sockaddr*)&server,&n);
    printf("Factorial of %d = %d\n",num,fact);

    close(server_sock);
    printf("[-]Disconnected from Server...\n");
    return 0;
}
