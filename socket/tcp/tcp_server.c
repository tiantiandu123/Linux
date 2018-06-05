#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
//./tcp_server 127.0.0.1 8080
void service(int sock,char*ip,int port)
{	
	char buf[1024];
	while(1){
		buf[0]=0;
		ssize_t s=read(sock,buf,sizeof(buf)-1);
		if(s>0){
			buf[s]=0;
			printf("[%s:%d] say#%s\n",ip,port,buf);
			write(sock,buf,strlen(buf));
		}
		else if(s==0){//write fd closed
			printf("client [%s:%d]quit!\n",ip,port);
			break;
		}else{
			printf("read error\n");
			break;
		}
	}
}
int main(int argc,char*argv[])
{
	if(argc!=3){
		printf("Usage:%s [ip] [port]\n",argv[0]);
		return 1;
	}
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0){
		perror("socket");
		return 2;
	}
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_addr.s_addr=inet_addr(argv[1]);
	local.sin_port=htons(atoi(argv[2]));
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0){
		printf("bind error\n");
		return 3;
	}
	if(listen(sock,5)<0){//listen sock
		perror("listen");
		return 4;
	}
	struct sockaddr_in peer;
	while(1){
		socklen_t len=sizeof(peer);
		int client_sock=accept(sock,(struct sockaddr*)&peer,&len);
		if(client_sock<0){
			printf("accept error\n");
			continue;
		}
		//sucess
		printf("get a new connect,[%s:%d]\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
		service(client_sock,inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
		close(client_sock);
	}
	return 0;
}
