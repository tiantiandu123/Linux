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
	if(chdir("/")<0){
		printf("child dir error\n");
		return;
	}
	close(0);
	close(1);
	close(2);
}
int main()
{
	mydaemon();
	while(1){
		sleep(1);
	}
	return 0;
}
