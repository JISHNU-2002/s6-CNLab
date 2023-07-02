#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(){
    int server_sock,client_sock;
    struct sockaddr_in server,client;
    server_sock = socket(AF_INET,SOCK_STREAM,0);
    if(server_sock < 0){
        printf("[-]TCP server socket error\n");
        exit(0);
    }else{
        printf("[+]TCP socket created\n");
    }
    server.sin_family = AF_INET;
    server.sin_port = 4000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int n = sizeof(server);
    client_sock = connect(server_sock,(struct sockaddr*)&server,n);
    if(client_sock < 0){
        printf("[-]client not connected\n");
        exit(0);
    }else{
        printf("[+]client connected\n");
    }

    char buf[1024],mail_f[50],mail_to[50],mail_body[1024];
    bzero(buf,sizeof(buf));
    strcpy(buf,"MAIL FROM : ");
    printf("Enter from address : ");
    gets(mail_f);
    strcat(buf,mail_f);
    send(server_sock,buf,sizeof(buf),0);

    bzero(buf,sizeof(buf));
    recv(server_sock,buf,sizeof(buf),0);
    if(strncmp(buf,"200",3)){
        printf("client side error\n");
    }else{
        printf("%s\n",buf);
        bzero(buf,sizeof(buf));
        strcpy(buf,"MAIL TO : ");
        printf("Enter to address : ");
        gets(mail_to);
        strcat(buf,mail_to);
        send(server_sock,buf,sizeof(buf),0);
    }

    bzero(buf,sizeof(buf));
    recv(server_sock,buf,sizeof(buf),0);
    if(strncmp(buf,"200",3)){
        printf("client side error\n");
    }else{
        printf("%s\n",buf);
        bzero(buf,sizeof(buf));
        strcpy(buf,"MAIL BODY :\n");
        printf("Enter the mail body :\n");
        
        int t=0;
        char c;
        while(1){
            c = getchar();
            if(c == '$'){
                mail_body[t] = '\0';
                break;
            }else{
                mail_body[t] = c;
                t++;
            }
        }
        
        strcat(buf,mail_body);
        send(server_sock,buf,sizeof(buf),0);
    }

    bzero(buf,sizeof(buf));
    recv(server_sock,buf,sizeof(buf),0);
    if(strncmp(buf,"200",3)){
        printf("client side error\n");
    }else{
        printf("%s\n",buf);
        bzero(buf,sizeof(buf));
        strcpy(buf,"client : END");
        printf("%s\n",buf);
        send(server_sock,buf,sizeof(buf),0);
    }
   
    close(server_sock);
    return 0;
}
