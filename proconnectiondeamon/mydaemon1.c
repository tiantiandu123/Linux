#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
void mydaemon(void)
{
	umask(0);
	pid_t id=fork();
	if(id<0){
		perror("fork()");
	}else if(id>0){//father
		exit(0);
	}
	setsid();//set new session
	signal(SIGCHLD,SIG_IGN);//ignore
	pid_t id1=fork();
	if(id1<0){
		perror("fork()");
	}else if(id1>0){//father
		exit(0);
	}
	if(chdir("/")<0){
		printf("child dir error\n");
		return;
	}
	close(0);
	int fd0;
	fd0=open("dev/null",O_RDWR);
	dup2(fd0,1);
	dup2(fd0,2);
}
int main()
{
	mydaemon();
	while(1){
		sleep(1);
	}
	return 0;
}
