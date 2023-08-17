#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

void resend(int ch,int c_sock){
    char buff2[60] = "resending frame - ";
    buff2[strlen(buff2)]=(ch)+'0';
    buff2[strlen(buff2)]='\0';
    printf("%s \n",buff2);
    write(c_sock, buff2, sizeof(buff2));
    usleep(1000);
}

int main(){
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server, client;
    
    server.sin_family = AF_INET;
    server.sin_port = 3000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if(bind(sock_fd, (struct sockaddr*)&server, sizeof(server)) == -1) {
        printf("Binding failed\n");
        return 0;
    }
    printf("\tServer Up\n Selective repeat scheme\n\n");

    listen(sock_fd, 10);
    int n = sizeof(client);
    int c_sock = accept(sock_fd, (struct sockaddr*)&client, &n);

    int rv1,rv2,rv3,tot=0,flag=0;
    char buff[50],buff2[50];
    struct timeval timeout1,timeout2,timeout3;
    time_t t1,t2;
    fd_set set1,set2,set3;

    while(tot<9){
        int toti=tot;
        for(int j=(0+toti);j<(3+toti);j++){
            bzero(buff,sizeof(buff));
            bzero(buff2,sizeof(buff2));
            buff2[strlen(buff2)]=(j)+'0';
            buff2[strlen(buff2)]='\0';
            printf("frame send : %s \n",buff2);
            write(c_sock, buff2, sizeof(buff2));
            usleep(1000);
        }
        for(int k=0+toti;k<(toti+3);k++){
            qq:
            FD_ZERO(&set1);
            FD_SET(c_sock, &set1);
            timeout1.tv_sec = 2;
            timeout1.tv_usec = 0;
            rv1 = select(c_sock + 1, &set1, NULL, NULL,&timeout1);
            
            if(rv1 == -1){
                perror("select error ");
            }else if(rv1 == 0){
                printf("Timeout for message : %d \n",k);
                resend(k,c_sock);
                goto qq;
            }else{
                read(c_sock, buff, sizeof(buff));
                printf("%s\n", buff);
                if(buff[0]=='n'){
                    resend((buff[strlen(buff)-1]-'0'),c_sock);
                    goto qq;
                }else{
                    tot++;
                }
            }
        }
    }
    close(c_sock);
    close(sock_fd);
    return 0;
}
