#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<math.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(){
    int server_sock,client_sock;
    struct sockaddr_in server,client;
    char buf[1024];
    int n = sizeof(client);

    server_sock = socket(AF_INET,SOCK_STREAM,0);    
    if(server_sock < 0){
        printf("[-]TCP server socket error\n");
        exit(0);
    }else{
        printf("[+]TCP server socket created\n");
    }
    server.sin_family = AF_INET;
    server.sin_port = 5000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int b = bind(server_sock,(struct sockaddr*)&server,sizeof(server));
    if(b < 0){
        printf("[-]TCP bind error\n");
        exit(0);
    }else{
        printf("[+]TCP bind success\n");
    }

    listen(server_sock,1);
    printf("[+]SERVER Listening\n");
    client_sock = accept(server_sock,(struct sockaddr*)&client,&n);

    int frame,ack,m,t,i;
    recv(client_sock,&m,sizeof(m),0);
    printf("\nNo of frames to be recieved = %d",m);
    recv(client_sock,&t,sizeof(t),0);
    printf("\n                    timeout = %d\n",t);
    int temp = (rand()%m)-1;
    
    while(1){
        recv(client_sock,&frame,sizeof(frame),0);
        ack = frame;
        if(frame == temp){
            printf("\n[-]Timeout Resend frame %d\n[-]ack %d send\n",frame,ack);
            ack = -1;
            temp = -1;
        }else{
            printf("\n[+]frame %d recieved successfully\n[+]ack %d send\n",frame,ack);
        }
        send(client_sock,&ack,sizeof(ack),0);
        if(ack == m-1){
            break;
        }
    }
    close(client_sock);
    close(server_sock);
    return 0;
}