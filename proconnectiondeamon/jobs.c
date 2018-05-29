#include<stdio.h>
#include<unistd.h>

int main()
{
	pid_t id=fork();
	if(id<0){
		perror("fork");
		return 1;
	}else if(id==0){//child
		while(1){
			printf("child %d is running\n",getpid());
			sleep(1);
		}
	}else{
			printf("parent(%d)is going to dead\n",getpid());
			sleep(5);
			exit(1);
	}
	return 0;
}

