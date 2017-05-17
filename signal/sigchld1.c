#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void handler(int signo)
{	
	int count=10;
	while(count--){
		printf("get a %d sig,pid:%d\n",signo,getpid());
		sleep(1);
	}
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
		waitpid(-1,NULL,0);
	//	sleep(1);
	}
	return 0;
}

		
