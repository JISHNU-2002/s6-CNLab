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
		printf("[-] socket creation error\n");
		exit(0);
	}
	printf("[+]tcp socket created\n");

	server.sin_family  = AF_INET;
	server.sin_port = 3000;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	int b = bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	if(b < 0){
		printf("[-]bind error\n");
		exit(0);
	}
	printf("[+]bind success\n");


	int l = listen(sockfd,1);
	if(l <0){
		printf("[-]server listen error\n");
		exit(0);
	}
	printf("[+]server listening , waiting for client\n");

	int n = sizeof(client);
	int a = accept(sockfd,(struct sockaddr*)&client,&n);
	if(a <0){
		printf("[-]client connection declined\n");
		exit(0);
	}
	printf("[+]client connection accepted\n\n");

	char mail_from[1024],mail_to[1024],mail_body[1024],c;
	int t=0;

	printf("From : ");
	gets(mail_from);
	send(a,mail_from,1024,0);

	printf("To : ");
	gets(mail_to);
	send(a,mail_to,1024,0);

	printf("\nEnter mail body : \n");
	while(1){
		c=getchar();
		if(c=='$'){
			mail_body[t]='\0';
			break;
		}else if(c=='\0'){
			continue;
		}else{
			mail_body[t++]=c;
		}
	}
	send(a,mail_body,1024,0);

	close(sockfd);
	printf("\n[+}mail send , client disconnected\n");

	return 1;
}
