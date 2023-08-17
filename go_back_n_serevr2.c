#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/time.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<fcntl.h>
int main() {
	int s_sock, c_sock;
	s_sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server,client;
	
	server.sin_family = AF_INET;
	server.sin_port = 9000;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(bind(s_sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
		printf("[-]Binding failed\n");
		return 0;
	}

	printf("[+]Server Up || Go back n (n=3) used to send 10 messages\n\n");
	listen(s_sock, 10);
	int n = sizeof(client);
	c_sock = accept(s_sock, (struct sockaddr*)&client, &n);

	time_t t1,t2;
	char msg[50]="frame :";
	char buff[50];
	int flag=0;
	fd_set set1,set2,set3;
	struct timeval timeout1,timeout2,timeout3;
	int rv1,rv2,rv3;
	int i=-1;

	qq:
		i=i+1;
		bzero(buff,sizeof(buff));
		char buff2[60];
		bzero(buff2,sizeof(buff2));
		strcpy(buff2,"frame :");
		buff2[strlen(buff2)]=i+'0';
		buff2[strlen(buff2)]='\0';
		printf("client :%s \n",buff2);
		write(c_sock, buff2, sizeof(buff2));
		usleep(1000);

		i=i+1;
		bzero(buff2,sizeof(buff2));
		strcpy(buff2,msg);
		buff2[strlen(msg)]=i+'0';
		printf("client :%s \n",buff2);
		write(c_sock, buff2, sizeof(buff2));
		i=i+1;
		usleep(1000);

	qqq:
		bzero(buff2,sizeof(buff2));
		strcpy(buff2,msg);
		buff2[strlen(msg)]=i+'0';
		printf("client :%s \n",buff2);
		write(c_sock, buff2, sizeof(buff2));
		FD_ZERO(&set1);
		FD_SET(c_sock, &set1);
		timeout1.tv_sec = 2;
		timeout1.tv_usec = 0;
		rv1 = select(c_sock + 1, &set1, NULL, NULL, &timeout1);
		if(rv1 == -1){
			perror("select error ");
		}else if(rv1 == 0){
			printf("\nGoing back from %d || timeout \n",i);
			i=i-3;
			goto qq;
		}else{
			read(c_sock, buff, sizeof(buff));
			printf("server : %s\n", buff);
			i++;
			if(i<=9)
				goto qqq;
		}

	qq2:
		FD_ZERO(&set2);
		FD_SET(c_sock, &set2);
		timeout2.tv_sec = 3;
		timeout2.tv_usec = 0;
		rv2 = select(c_sock + 1, &set2, NULL, NULL, &timeout2);
		if(rv2 == -1){
			perror("select error "); // an error accured
		}else if(rv2 == 0){
			printf("\nGoing back from %d || timeout on last 2\n",i-1);
			i=i-2;
			bzero(buff2,sizeof(buff2));
			strcpy(buff2,msg);
			buff2[strlen(buff2)]=i+'0';
			write(c_sock, buff2, sizeof(buff2));
			usleep(1000);

			i++;
			bzero(buff2,sizeof(buff2));
			strcpy(buff2,msg);
			buff2[strlen(buff2)]=i+'0';
			write(c_sock, buff2, sizeof(buff2));
			goto qq2;
		} // a timeout occured
		else{
			read(c_sock, buff, sizeof(buff));
			printf("server: %s\n", buff);
			bzero(buff,sizeof(buff));
			read(c_sock, buff, sizeof(buff));
			printf("server: %s\n", buff);
		}

	close(c_sock);
	close(s_sock);
	return 0;
}
