#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(){
    int server_sock,client_sock,b,n,num,fact=1,i;
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

    b = bind(server_sock,(struct sockaddr*)&server,sizeof(server));
    if(b < 0){
        printf("[-]UDP bind error\n");
        exit(0);
    }else{
        printf("[+]UDP bind successfull\n");
    }

    printf("[+]Server ready , waiting for Client\n");
    n = sizeof(client);

    //only for messaging server-client
    for(;;){
        recvfrom(server_sock,buf,sizeof(buf),0,(struct sockaddr*)&client,&n);
        if(strcmp(buf,"end")==0){
            break;
        }
        printf("\nclient : %s",buf);

        printf("\nserver : ");
        gets(buf);
        sendto(server_sock,buf,sizeof(buf),0,(struct sockaddr*)&client,n);
        if(strcmp(buf,"end")==0){
            break;
        }
    }

    //for calculating factorial of a number sent by client
    recvfrom(server_sock,&num,sizeof(num),0,(struct sockaddr*)&client,&n);
    if(num == 0){
        fact = 1;
    }else{
       for(i=1;i<=num;i++){
            fact = fact*i;
       }
    }
    sendto(server_sock,&fact,sizeof(fact),0,(struct sockaddr*)&client,n);
    printf("Factorial calculated\n");

    close(client_sock);
    printf("[-]Client disconnected...\n");
    close(server_sock);
    return 0;
}
