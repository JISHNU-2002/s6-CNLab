#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main(){
	struct sockaddr_in server,client;
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0){
		printf("[-]socket creation error\n");
		exit(0);
	}
	printf("[+]tcp socket created\n");
		
	server.sin_family  = AF_INET;
	server.sin_port = 3000;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	int n = sizeof(server);
	int c = connect(sockfd,(struct sockaddr*)&server,n);
	if(c < 0){
		printf("[-]connection error\n");
		exit(0);
	}
	printf("[+]connected to server\n\n");
		
	char mail_from[1024],mail_to[1024],mail_body[1024];

	recv(sockfd,mail_from,1024,0);
	recv(sockfd,mail_to,1024,0);
	recv(sockfd,mail_body,1024,0);
	
	printf("From : %s\n",mail_from);
	printf("To: %s\n",mail_to);
	printf("\n\n%s\n",mail_body);

	close(sockfd);
	printf("[+]mail recieved , client disconnecting\n");
	return 0;
}
