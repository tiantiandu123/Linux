#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<strings.h>
#include<stdlib.h>
#include<string.h>
void service(int sock)
{
	char buf[10240];
	read(sock,buf,sizeof(buf));
	const char*response="HTTP/1.0 200 OK\n\n<html><head>hello world</head></html>\n";

	write(sock,response,strlen(response));
}
int startup(int port)
{
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0){
		perror("socket");
		return 2;
	}
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(port);
	local.sin_addr.s_addr=htonl(INADDR_ANY);
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0){
		perror("bind error\n");
		return 3;
	}
	if(listen(sock,5)<0){
		perror("listen\n");
		return 4;
	}
	return sock;
}
int main(int argc,char*argv[])
{
	if(argc!=2){
		printf("Usage:%s [port]\n",argv[0]);
		return 1;
	}
	int listen_sock=startup(atoi(argv[1]));
//	daemon(0,0);
	while(1){
		struct sockaddr_in peer;
		bzero(&peer,sizeof(peer));
		socklen_t len=sizeof(peer);
		int client_sock=accept(listen_sock,(struct sockaddr*)&peer,&len);
		if(client_sock<0){
			perror("accept");
			continue;
		}
		pid_t id=fork();
		if(id==0){
			close(listen_sock);
			if(fork>0){
				exit(0);
			}
			service(client_sock);
			close(client_sock);
			exit(1);
		}else if(id>0){
			close(client_sock);
			waitpid(id,NULL,0);
		}else{
			printf("fork error\n");
			continue;
			}
	}
	return 0;
}
			
