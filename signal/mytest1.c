#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
void handler(int signo)
{
	printf("get a %d signo\n",signo);
//	exit(1);
}
void show_pending(sigset_t *pending)
{
	int i=1;
	for(;i<32;i++)
	{
		if(sigismember(pending,i)){
			printf("1");
		}else{
			printf("0");
		}
	}
	printf("\n");
}
	
int main()
{
	sigset_t set,oset,pending;
	sigemptyset(&set);
	sigaddset(&set,2);
	signal(2,handler);
	sigprocmask(SIG_SETMASK,&set,&oset);
	int count=0;
	while(1){
		sigpending(&pending);
		show_pending(&pending);
		sleep(1);
		count++;
		if(count==15){					
			sigprocmask(SIG_SETMASK,&oset,NULL);
		}
	}
	return 0;
}
