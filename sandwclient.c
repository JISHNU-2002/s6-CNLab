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
    int n = sizeof(server);

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

    printf("[+]CLIENT Ready\n");
    client_sock = connect(server_sock,(struct sockaddr*)&server,sizeof(server));
    if(client_sock < 0){
        printf("[-]CLIENT connection error\n");
        exit(0);
    }else{
        printf("[+]CLIENT connection successfull\n");
    }

    int frame[50],m,t,ack,i;
    printf("\nEnter no of frames to send = ");
    scanf("%d",&m);
    send(server_sock,&m,sizeof(m),0);
    printf("             Enter timeout = ");
    scanf("%d",&t);
    send(server_sock,&t,sizeof(t),0);
    for(i=0;i<m;i++){
        frame[i] = i;
    }
    i=0;

    while(1){
        printf("\n[+]frame %d send\n",frame[i]);
        send(server_sock,&frame[i],sizeof(frame[i]),0);
        recv(server_sock,&ack,sizeof(ack),0);

        if(ack == m-1){
            printf("[+]ack recieved successfully : %d\n",ack);
            break;
        }
        if(ack == frame[i]){
            i++;
            printf("[+]ack recieved successfully : %d\n",ack);
        }else{
            sleep(t);
            printf("[-]ack RESENDing frame %d\n",frame[i]);
        }
    }
    close(server_sock);
    return 0;
}