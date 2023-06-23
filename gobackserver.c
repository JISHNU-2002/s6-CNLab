#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>
#include<fcntl.h>

int main(){
    int s_sock,c_sock;
    struct sockaddr_in server,client;
    s_sock = socket(AF_INET,SOCK_STREAM,0);
    if(s_sock < 0){
        printf("[-]error\n");
        exit(0);
    }else{
        printf("[+]\n");
    }
    server.sin_family = AF_INET;
    server.sin_port = 7000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("[+]server ready\n");

    int b = bind(s_sock,(struct sockaddr*)&server,sizeof(server));
    if(b < 0){
        printf("[-]error\n");
        exit(0);
    }else{
        printf("[+]\n");
    }

    listen(s_sock,10);
    printf("[+]listening\n");

    int n = sizeof(client);
    c_sock = accept(s_sock,(struct sockaddr*)&client,&n);
    printf("[+]server up \tGo back n(3) used to send 10 msgs\n");

    c_sock = accept(s_sock,(struct sockaddr*)&client,&n);
    if(c_sock < 0){
        printf("[-]client not accepted\n");
        exit(0);
    }else{
        printf("[+]client accepted\n");
    } 
    
    time_t t1,t2;
    struct timeval timeout1,timeout2;
    fd_set set1,set2;
    int rv1,rv2;
    char buf[50],msg[50];
    int i = -1;

    label1:
        i++;
        bzero(buf,sizeof(buf));
        strcpy(buf,"server : ");
        buf[strlen(buf)] = i+'0';
        buf[strlen(buf)] = '\0';
        printf("msg send to client - %s\n",buf);
        write(c_sock,buf,sizeof(buf));
        sleep(1);

        i++;
        bzero(buf,sizeof(buf));
        strcpy(buf,"server : ");
        buf[strlen(buf)] = i+'0';
        buf[strlen(buf)] = '\0';
        printf("msg send to client - %s\n",buf);
        write(c_sock,buf,sizeof(buf));
        sleep(1);
        i++;
    
    label2:
        bzero(buf,sizeof(buf));
        strcpy(buf,"server : ");
        buf[strlen(buf)] = i+'0';
        buf[strlen(buf)] = '\0';
        printf("msg send to client - %s\n",buf);
        write(c_sock,buf,sizeof(buf));
        sleep(1);

        FD_ZERO(&set1);
        FD_SET(c_sock,&set1);
        timeout1.tv_sec = 2;
        timeout1.tv_usec = 0;
        rv1 = select(c_sock+1,&set1,NULL,NULL,&timeout1);
        if(rv1 < 0){
            printf("select error\n");
        }else if(rv1 == 0){
            printf("going back from %d || timeout\n",i);
            i=i-1;
            goto label1;
        }else{
            printf("msg send to client - %s\n",buf);
            i++;
            if(i<=9){
                goto label2;
            }
        }
    
    label3:
        FD_ZERO(&set2);
        FD_SET(c_sock,&set2);
        timeout2.tv_sec = 3;
        timeout2.tv_usec = 0;
        rv2 = select(c_sock+1,&set2,NULL,NULL,&timeout2);
        if(rv2 < 0){
            printf("select error\n");
        }else if(rv2 == 0){
            printf("going back from %d last 2 || timeout\n",i-1);
            i = i-2;
            bzero(buf,sizeof(buf));
            strcpy(buf,"server : ");
            buf[strlen(buf)] = i+'0';
            buf[strlen(buf)] = '\0';
            printf("msg send to client - %s\n",buf);
            write(c_sock,buf,sizeof(buf));
            sleep(1);

            i++;
            bzero(buf,sizeof(buf));
            strcpy(buf,"server : ");
            buf[strlen(buf)] = i+'0';
            buf[strlen(buf)] = '\0';
            printf("msg send to client - %s\n",buf);
            write(c_sock,buf,sizeof(buf));
            sleep(1);

            goto label3;
        }else{
            bzero(buf,sizeof(buf));
            read(c_sock,buf,sizeof(buf));
            printf("client : %s\n",buf);

            bzero(buf,sizeof(buf));
            read(c_sock,buf,sizeof(buf));
            printf("client : %s\n",buf);
        }
    close(c_sock);
    close(s_sock);

    return 0;
}