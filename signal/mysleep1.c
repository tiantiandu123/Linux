#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void handler()
{}
int mysleep(int timeout)
{
	struct sigaction act,oact;
	act.sa_handler=handler;
	act.sa_flags=0;
	sigemptyset(&act.sa_mask);//init;
	sigaction(14,&act,&oact);
	alarm(timeout);
	pause();
	int unsleep=alarm(0);//empty
	sigaction(14,&oact,NULL);
	return unsleep;
}
int main()
{
	while(1){
		mysleep(2);
		printf("two seconds passed\n");
	}
	return 0;
}
