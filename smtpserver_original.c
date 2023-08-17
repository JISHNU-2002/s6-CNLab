#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    struct sockaddr_in server, client;
    char str[1024];

    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0){
        printf("[-]TCP socket error\n");
    }
    printf("[+]TCP socket created\n");

    server.sin_family = AF_INET;
    server.sin_port=8000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int b = bind(sockfd,(struct sockaddr*)&server,sizeof(server));
    if(b < 0){
        printf("[-]bind error\n");
    }
    printf("[+]bind success\n");

    listen(sockfd,1);
    printf("[+]server listening\n");

    int n=sizeof(client);
    int c_sock = accept(sockfd,(struct sockaddr*)&client,&n);
    printf("[+]client accepted\n");

    recv(c_sock,str,sizeof(str),0);
    printf("\n[+]msg from client : %s\n",str);

    printf("[+]sending greeting msg to client\n");
    strcpy(str,"220 127.0.0.1");
    send(c_sock,str,sizeof(str),0);
    
    recv(c_sock,str,sizeof(str),0);
    if(strncmp(str,"HELLO",5)){
        printf("[-]HELLO expected from client\n");
    }
    printf("[+]client : %s\n",str);
    
    printf("[+]sending response to client\n");
    strcpy(str,"250 - OK");
    send(c_sock,str,sizeof(str),0);
        
    recv(c_sock,str,sizeof(str),0);
    if(strncmp(str,"MAIL FROM",9)){
        printf("[-]MAIL FROM expected from client\n");
    }
    printf("[+]client : %s\n",str);

    printf("[+]sending response to client\n");
    strcpy(str,"250 - OK");
    send(c_sock,str,sizeof(str),0); 

    printf("[+]receiving to address\n");
    recv(c_sock,str,sizeof(str),0);
    if(strncmp(str,"MAIL TO",7)){
        printf("[-]MAIL TO expected from client\n");
    }
    printf("[+]client : %s\n",str);

    printf("[+]sending response to client\n");
    strcpy(str,"250 - OK");
    send(c_sock,str,sizeof(str),0); 

    recv(c_sock,str,sizeof(str),0);
    if(strncmp(str,"DATA",4)){
        printf("[-]DATA expected from client\n");
    }
    printf("[+]client : %s\n",str);

    printf("[+]sending response to client\n");
    strcpy(str,"354 - GO AHEAD");
    send(c_sock,str,sizeof(str),0);
    
    recv(c_sock,str,sizeof(str),0);
    if(strncmp(str,"MAIL BODY",9)){
        printf("[-]MAIL BODY expected from client\n");
    }
    printf("[+]Mail body received\n");
    printf("[+]client : %s\n",str);

    printf("[+]sending response to client\n");
    strcpy(str,"354 - GO AHEAD");
    send(c_sock,str,sizeof(str),0);
    
    recv(c_sock,str,sizeof(str),0);
    if(strncmp(str,"QUIT",4)){
        printf("[-]QUIT expected from client\n");
    }
    printf("[+]client : %s\n",str);

    printf("[+]sending confirmation to client\n");
    strcpy(str,"221 - OK");
    send(c_sock,str,sizeof(str),0);

    close(sockfd);
    printf("[-]server disconnected\n");
    return 0;
}