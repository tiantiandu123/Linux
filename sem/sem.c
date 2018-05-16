#include"comm.h"

int main()
{
	int semid=createSemset(1);
	initSemset(semid,0,1);
	pid_t pid=fork();
	if(pid==0){//child
		int _semid=getSemset(0);
		while(1){
			P(_semid,0);
			printf("A");
			fflush(stdout);
			sleep(1);
			printf("A");
			fflush(stdout);
			sleep(1);
			V(_semid,0);
		}
	}
	else{
			while(1){
			P(semid,0);
			printf("B");
			fflush(stdout);
			sleep(1);
			printf("B");
			fflush(stdout);
			sleep(1);
			V(semid,0);
		}
		wait(NULL);
	}
	destroySemset(semid,0);
	return 0;
}
