#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int isfaulty(){ 
    int d=rand()%4;
    return (d>2);
}

int main(){
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = 3000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    connect(sock_fd, (struct sockaddr*)&server, sizeof(server));

    printf("\n\tClient -with individual acknowledgement scheme\n\n");
    char msg1[50]="positive ack recieved for frame - ";
    char msg3[50]="negative ack recieved for frame - ";
    char msg2[50];
    char buff[100];
    int count=-1,flag=1;
    
    while(count<8){
        bzero(buff,sizeof(buff));
        bzero(msg2,sizeof(msg2));

        if(count==7&&flag==1){
            printf("Timeout occured\n"); //simulate loss
            flag=0;
            read(sock_fd,buff,sizeof(buff));
            continue;
        }

        read(sock_fd, buff, sizeof(buff));
        char i=buff[strlen(buff)-1];
        printf("server msg : %s \n",buff);
        int isfault=isfaulty();
        printf("error status : %d \n",isfault);
        
        if(isfault){
            strcpy(msg2,msg3);
            printf("negative ack send for frame - %c\n",i);
        }
        else{
            printf("positive ack send for frame - %c \n",i);
            strcpy(msg2,msg1);
            count++;
        }
        msg2[strlen(msg2)]=i;
        write(sock_fd,msg2, sizeof(msg2));
    }
}