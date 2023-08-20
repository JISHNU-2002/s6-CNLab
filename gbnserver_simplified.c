#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    struct sockaddr_in server,client;

    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        printf("[-]socket creation error \n");
        exit(0);
    }
    printf("[+]socket creation successful \n");

    server.sin_family = AF_INET;
    server.sin_port = 4000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int b=bind(sockfd,(struct sockaddr*)&server,sizeof(server));
    if(b<0){
        printf("[-]Bind error \n");
        exit(0);
    }
    printf("[+]Binding successful \n");


    listen(sockfd,1);
    int n=sizeof(client);
    int client_sock=accept(sockfd,(struct sockaddr*)&client,&n);
    if(client_sock<0){
        printf("[-]connection error \n");
        exit(0);
    }
    printf("[+]connection successful \n");

    int frame[1024],ack,nf,gbn,t,i;
    printf("Number of frames to send = ");
    scanf("%d",&nf);
    send(client_sock,&nf,sizeof(nf),0);

    printf("Enter timeout = ");
    scanf("%d",&t);
    send(client_sock,&t,sizeof(t),0);

    printf("Enter the go back n = ");
    scanf("%d",&gbn);

    for(i=0;i<nf;i++){
        frame[i]=i;
    }
    i=0;

    while(1){
        send(client_sock,&frame[i],sizeof(frame[i]),0);
        printf("[+]frame [%d] send \n",frame[i]);
        recv(client_sock,&ack,sizeof(ack),0);

        if(ack == frame[i]){
            printf("[+]acknowledgement %d recieved \n",ack);
            i++;
        }else{
            sleep(t);
            printf("[-]timeout || go back n from frame[%d]\n",frame[i]);
            i=i-gbn+1;
        }

        if(ack==nf-1){
            break;
        }
    }

    printf("[+]client disconnected \n");
    close(sockfd);
    return 0;
}