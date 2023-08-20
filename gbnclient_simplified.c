#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<math.h>

int main(){
    struct sockaddr_in server,client;
    int sockfd,n,con;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        printf("[-]Socket creation error \n");
        exit(0);
    }
    printf("[+]socket creation successful \n");

    server.sin_family = AF_INET;
    server.sin_port = 4000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    n=sizeof(server);
    con=connect(sockfd,(struct sockaddr*)&server,n);
    if(con<0){
        printf("[-]Connection error \n");
        exit(0);
    }
    printf("[+]connection successful \n");

    int nf,t,frame,ack;

    recv(sockfd,&nf,sizeof(nf),0);
    printf("Number of frames to be recieved = %d",nf);
    int temp=rand()%nf;

    recv(sockfd,&t,sizeof(t),0);
    printf("Timeout = %d \n",t);

    while(1){
        recv(sockfd,&frame,sizeof(frame),0);
        ack=frame;

        if(ack == temp){
            sleep(t);
            printf("[-]timeout || go back n\n");
            ack = -1;
            temp = -1;
        }else{
            printf("[+]frame [%d] recieved \n",frame);
            printf("[+]acknowledgement [%d] send \n",ack);
        }
        send(sockfd,&ack,sizeof(ack),0);

        if(ack==nf-1){
            break;
        }
    }

    printf("[+]Server disconnected \n");
    close(sockfd);
    return 0;
}