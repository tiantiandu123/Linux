#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
//./tcp_client ip 8080

typedef struct request
{
	int a;
	int b;
}request;
typedef struct response
{
	int sum;
}response;
int main(int argc,char*argv[])
{
	if(argc!=3){
		printf("Usage:%s [ip][port]",argv[0]);
		return 1;
	}
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0){
		printf("socket");
		return 2;
	}
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[2]));
	server.sin_addr.s_addr=inet_addr(argv[1]);
	if(connect(sock,(struct sockaddr*)&server,sizeof(server))<0){
		printf("connect error\n");
		return 3;
	}
	char buf[1024];
	while(1){
		printf("client#: ");
		fflush(stdout);
//		request req;
//		response res;
//		scanf("%d %d",&req.a,&req.b);
//		write(sock,&req,sizeof(req));
//		read(sock,&res,sizeof(res));
//		printf("%d +%d=%d",req.a,req.b,res.sum);
//		fflush(stdout);
		ssize_t s=read(0,buf,sizeof(buf)-1);
		if(s>0){
			buf[s-1]=0;
			if(strcmp("quit",buf)==0){
				printf("client quit\n");
				break;
			}
			write(sock,buf,strlen(buf));
			s=read(sock,buf,sizeof(buf)-1);
			buf[s]=0;
			printf("server echo# %s\n",buf);
		}
	}
	close(sock);
	return 0;
}
