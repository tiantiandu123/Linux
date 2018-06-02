#include<stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
int main(int argc,char*argv[])
{
	if(argc!=3){
		printf("Usage:%s [ip] [port]\n",argv[0]);
		return 4;
	}
	int sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0){
		perror("socket");
		return 1;
	}
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[2]));
	server.sin_addr.s_addr=inet_addr(argv[1]);
	char buf[1024];
	struct sockaddr_in peer;
	socklen_t len=sizeof(peer);
	while(1){
		printf("please enter# ");
		fflush(stdout);
		ssize_t s=read(0,buf,sizeof(buf)-1);
		if(s>0){//read sucess
			buf[s-1]=0;
			sendto(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&server,sizeof(server));
			ssize_t s1=recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
			if(s1>0){
				buf[s]=0;
				printf("server echo# %s\n",buf);
				}
			}
		}

	close(sock);
	return 0;
}
