#include<stdio.h>
#include<signal.h>

void handler(int signo)
{
	printf("get a sig %d\n",signo);
}
int main()
{
	struct sigaction act,oact;
	act.sa_handler=handler;
	act.sa_flags=0;
	//sigemptyset(&act.sa_mask);//init
	sigaction(2,&act,&oact);
	while(1){
		printf("hello world\n");
		usleep(100000);
	}
	return 0;
}
