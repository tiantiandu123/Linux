#include<stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
void service(int sock)
{
	char buf[128];
	struct sockaddr_in peer;
	socklen_t len=sizeof(peer);
	while(1){
		buf[0]=0;
		ssize_t s=recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
		if(s>0){
			buf[s]=0;
			printf("[%s:%d]#%s\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port),buf);
			sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&peer,len);
		}
	}
}


int main(int argc,char*argv[])
{	
	if(argc!=3){
		printf("Usage:%s [ip] [port]\n",argv[0]);
		return 4;
	}
	int sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0){
		printf("socket error!\n");
		return 2;
	}
	//dong something between open and close
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(atoi(argv[2]));
	local.sin_addr.s_addr=inet_addr(argv[1]);
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0){
		printf("bind error!\n");
		return 3;
	}
	service(sock);
	close(sock);
	return 0;
}
