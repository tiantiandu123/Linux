#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void handler(int signo)
{
	while(waitpid(-1,NULL,WNOHANG)>0){
		printf("get a %d sig,pid:%d\n",signo,getpid());
	}
	printf("child is quit\n",getpid());
}
int main()
{
	pid_t pid=fork();
	if(pid<0){
		perror("fork()");
	}
	else if(pid==0){//child
		printf("child:%d\n",getpid());
		exit(1);
	}
	else{//father

		signal(SIGCHLD,handler);
		while(1){
			printf("father proc is doing something\n");
			sleep(1);
		}
	}
	return 0;
}

