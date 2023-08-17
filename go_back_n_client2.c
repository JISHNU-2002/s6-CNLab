#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/time.h>
#include<sys/wait.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
int main(){
    int c_sock,flag=1,flg=1;
    char msg1[50]="[+]acknowledgement of :",msg2[50],buff[100];
    c_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = 9000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(c_sock, (struct sockaddr*)&server, sizeof(server)) == -1){
        printf("[-]Connection failed");
        return 0;
    }
    printf("\n[+]server - with individual acknowledgement scheme\n\n");
    for(int i=0;i<=9;i++) {
        flg=1;
        bzero(buff,sizeof(buff));
        bzero(msg2,sizeof(msg2));
        if(i==8 && flag==1){
            printf("[-]here\n"); //simulating loss
            flag=0;
            read(c_sock,buff,sizeof(buff));
        }
        int n = read(c_sock, buff, sizeof(buff));
        if(buff[strlen(buff)-1]!=i+'0'){ //out of order
            printf("[-]Discarded as out of order \n");
            i--;
         }else{
            printf("%s\n",buff);
            printf("[+]Acknowledgement %d sent for message\n\n",i);
            strcpy(msg2,msg1);
            msg2[strlen(msg2)]=i+'0';
            write(c_sock,msg2, sizeof(msg2));
        }   
    }
    close(c_sock);
    return 0;
}
