#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define BUF_SIZE 256

int main(){
    struct sockaddr_in server,client;
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0){
        printf("[-]TCP socket error\n");
    }
    printf("[+]TCP socket created\n");

    server.sin_family = AF_INET;
    server.sin_port = 8000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("\n[+]client ready\n");
    int n=sizeof(server);
    int con = connect(sockfd,(struct sockaddr*)&server,n);
    printf("[+]connected\n");

    int t=0;
    char str[1024],mail_f[1024],mail_to[1024],mail_body[1024],c;

    strcpy(str,"Hi");
    printf("\n[+]sending Hi to server\n");
    send(sockfd,str,sizeof(str),0);

    recv(sockfd,str,sizeof(str),0);
    if(strncmp(str,"220",3)){
        printf("[-]cannot established - code 220 expected\n");
    }
    printf("[+]Greeting msg is : %s",str);

    printf("[+]sending HELLO\n");
    strcpy(str,"HELLO 127.0.0.1");
    send(sockfd,str,sizeof(str),0);

    printf("[+]receiving from server\n");
    recv(sockfd,str,sizeof(str),0);
    if(strncmp(str,"250",3)){
        printf("[-]OK not received from server\n");
    }
    printf("[+]server : %s\n",str);

    printf("\n[+]Enter FROM address : ");
    scanf("%s",mail_f);
    strcpy(str,"MAIL FROM : ");
    strcat(str,mail_f);
    send(sockfd,str,sizeof(str),0);

    printf("\n[+]receiving from server\n");
    recv(sockfd,str,sizeof(str),0);
    if(strncmp(str,"250",3)){
        printf("[-]OK not received from server\n");
    }
    printf("[+]server : %s\n",str);

    printf("\n[+]Enter TO address : ");
    scanf("%s",mail_to);
    strcpy(str,"MAIL TO : ");
    strcat(str,mail_to);
    send(sockfd,str,sizeof(str),0);

    printf("\n[+]receiving from server\n");
    recv(sockfd,str,sizeof(str),0);
    if(strncmp(str,"250",3)){
        printf("[-]OK not received from server\n");
    }
    printf("[+]server : %s\n",str);

    printf("[+]sending data to server\n");
    strcpy(str,"DATA");
    send(sockfd,str,sizeof(str),0);

    printf("\n[+]receiving from server\n");
    recv(sockfd,str,sizeof(str),0);
    if(strncmp(str,"354",3)){
        printf("[-]OK not received from server\n");
    }
    printf("[+]server : %s\n",str);

    printf("\n[+]Enter mail body\n");
    while(1){
        c=getchar();
        if(c=='$'){
            mail_body[t]='\0';
            break;
        }else{
            mail_body[t]=c;
            t++;
        }
    }
    strcpy(str,"MAIL BODY : \n");
    strcat(str,mail_body);
    send(sockfd,str,sizeof(str),0);

    printf("\n[+]receiving from server\n");
    recv(sockfd,str,sizeof(str),0);
    if(strncmp(str,"354",3)){
        printf("[-]OK not received from server\n");
    }
    printf("[+]server : %s\n",str);

    printf("[+]sending QUIT to server\n");
    strcpy(str,"QUIT");
    send(sockfd,str,sizeof(str),0);

    recv(sockfd,str,sizeof(str),0);
    if(strncmp(str,"221",3)){
        printf("[-]OK not received from server\n");
    }
    printf("[+]server : %s\n",str);

    close(sockfd);
    printf("[-]client disconnected\n");
    return 0;
}